//                                               -*- C++ -*-
/**
 *  @brief VineCopula
 *
 *  Copyright 2005-2024 Airbus-EDF-IMACS-ONERA-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "otvine/VineCopula.hxx"
#include <openturns/PersistentObjectFactory.hxx>
#include <openturns/ClaytonCopula.hxx>
#include <openturns/GumbelCopula.hxx>
#include <openturns/FrankCopula.hxx>

#include <vinecopulib.hpp>

using namespace OT;

namespace OTVINE
{

CLASSNAMEINIT(VineCopula);

static Factory<VineCopula> Factory_VineCopula;


/* Default constructor */
VineCopula::VineCopula()
  : DistributionImplementation()
{
  isCopula_ = true;
  setName("VineCopula");
}

VineCopula::VineCopula(const Pointer<vinecopulib::Vinecop> & p_vinecop)
  : DistributionImplementation()
  , p_vinecop_(p_vinecop)
{
  isCopula_ = true;
  setName("VineCopula");
  setDimension(p_vinecop->get_dim());
}

/* Virtual constructor method */
VineCopula * VineCopula::clone() const
{
  return new VineCopula(*this);
}

/* Get the PDF of the distribution */
Scalar VineCopula::computePDF(const Point & point) const
{
  const UnsignedInteger dimension = getDimension();
  Eigen::MatrixXd u(1, dimension);
    for (UnsignedInteger j = 0; j < dimension; ++ j)
      u(0, j) = point[j];
  return p_vinecop_->pdf(u)[0];
}

/* Get the CDF of the distribution */
Scalar VineCopula::computeCDF(const Point & point) const
{
  const UnsignedInteger dimension = getDimension();
  Eigen::MatrixXd u(1, dimension);
  for (UnsignedInteger j = 0; j < dimension; ++ j)
    u(0, j) = point[j];
  return p_vinecop_->cdf(u)[0];
}

/* Get one realization of the distribution */
Point VineCopula::getRealization() const
{
  const UnsignedInteger dimension = getDimension();
  const Eigen::MatrixXd u(p_vinecop_->simulate(1));
  Point result(dimension);
  for (UnsignedInteger j = 0; j < dimension; ++ j)
    result[j] = u(0, j);
  return result;
}

Sample VineCopula::getSample(const UnsignedInteger size) const
{
  const UnsignedInteger dimension = getDimension();
  const Eigen::MatrixXd u(p_vinecop_->simulate(size));
  Sample result(size, dimension);
  for (UnsignedInteger i = 0; i < size; ++ i)
    for (UnsignedInteger j = 0; j < dimension; ++ j)
      result(i, j) = u(i, j);
  return result;
}

/* Parameters value accessor */
Point VineCopula::getParameter() const
{
  return {};
}

void VineCopula::setParameter(const Point & parameter)
{
  if (parameter.getSize() != 0)
    throw InvalidArgumentException(HERE) << "Error: expected 0 value, got " << parameter.getSize();
}

/* Parameters description accessor */
Description VineCopula::getParameterDescription() const
{
  return {};
}

/* Comparison operator */
Bool VineCopula::operator ==(const VineCopula & other) const
{
  if (this == &other) return true;
  return false;
}

Bool VineCopula::equals(const DistributionImplementation & other) const
{
  const VineCopula* p_other = dynamic_cast<const VineCopula*>(&other);
  return p_other && (*this == *p_other);
}

/* String converter */
String VineCopula::__repr__() const
{
  OSS oss;
  oss << "class=" << VineCopula::GetClassName() << " " << p_vinecop_->str();
  return oss;
}

Distribution VineCopula::asNative() const
{
  if (p_vinecop_->get_dim() != 2)
    throw NotYetImplementedException(HERE) << "dim is not 2";
  std::vector<std::vector<vinecopulib::Bicop> > pairs = p_vinecop_->get_all_pair_copulas();
  if (pairs.size() != 1 && pairs[0].size() != 1)
    throw NotYetImplementedException(HERE) << "tree contains more than one node";
  vinecopulib::Bicop bicop = pairs[0][0];
  int rotation = bicop.get_rotation();
  if (rotation != 0)
    throw NotYetImplementedException(HERE) << "rotation is not 0";
  const Scalar theta = bicop.get_parameters()(0, 0);
  if (bicop.get_family_name() == "Clayton")
    return ClaytonCopula(theta);
  else if (bicop.get_family_name() == "Frank")
    return FrankCopula(theta);
  else if (bicop.get_family_name() == "Gumbel")
    return GumbelCopula(theta);
  else
    throw NotYetImplementedException(HERE) << "unknown family: " << bicop.get_family_name();
}

/* Method save() stores the object through the StorageManager */
void VineCopula::save(Advocate & adv) const
{
  DistributionImplementation::save(adv);
}

/* Method load() reloads the object from the StorageManager */
void VineCopula::load(Advocate & adv)
{
  DistributionImplementation::load(adv);
}


} /* namespace OTVINE */
