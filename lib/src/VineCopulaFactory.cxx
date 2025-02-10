//                                               -*- C++ -*-
/**
 *  @brief VineCopulaFactory
 *
 *  Copyright 2005-2025 Airbus-EDF-IMACS-ONERA-Phimeca
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
#include "otvine/VineCopulaFactory.hxx"
#include <openturns/PersistentObjectFactory.hxx>
#include <openturns/ClaytonCopula.hxx>
#include <openturns/GumbelCopula.hxx>
#include <openturns/FrankCopula.hxx>

#include <vinecopulib.hpp>

using namespace OT;

namespace OTVINE
{

CLASSNAMEINIT(VineCopulaFactory);

static Factory<VineCopulaFactory> Factory_VineCopulaFactory;


/* Default constructor */
VineCopulaFactory::VineCopulaFactory()
  : DistributionFactoryImplementation()
{
  // Nothing to do
}

/* Virtual constructor method */
VineCopulaFactory * VineCopulaFactory::clone() const
{
  return new VineCopulaFactory(*this);
}

/* example of a func that return a point squared. */
Distribution VineCopulaFactory::build(const Sample & sample) const
{
  const UnsignedInteger dimension = sample.getDimension();
  const UnsignedInteger size = sample.getSize();
  Eigen::MatrixXd data(size, dimension);
  for (UnsignedInteger i = 0; i < size; ++ i)
    for (UnsignedInteger j = 0; j < dimension; ++ j)
      data(i, j) = sample(i, j);
  Pointer <vinecopulib::Vinecop> p_vinecop = new vinecopulib::Vinecop(dimension);
  std::vector<vinecopulib::BicopFamily> family_set;
#if 0
  family_set = {
    vinecopulib::BicopFamily::clayton,
    vinecopulib::BicopFamily::gumbel,
    vinecopulib::BicopFamily::frank};
#endif
  vinecopulib::FitControlsVinecop controls(family_set);
  controls.set_allow_rotations(false);
  p_vinecop->select(data, controls);

#if 0
  std::vector<std::vector<vinecopulib::Bicop> > pairs = p_vinecop->get_all_pair_copulas();
  if (p_vinecop->get_dim() == 2 && pairs.size() == 1 && pairs[0].size() == 1)
  {
    vinecopulib::Bicop bicop = pairs[0][0];
    int rotation = bicop.get_rotation();
    if (rotation == 0)
    {
      const Scalar theta = bicop.get_parameters()(0, 0);
      if (bicop.get_family_name() == "Clayton")
        return ClaytonCopula(theta);
      else if (bicop.get_family_name() == "Frank")
        return FrankCopula(theta);
      else if (bicop.get_family_name() == "Gumbel")
        return GumbelCopula(theta);
    }
  }
#endif
  return VineCopula(p_vinecop);
}


/* String converter */
String VineCopulaFactory::__repr__() const
{
  OSS oss;
  oss << "class=" << VineCopulaFactory::GetClassName();
  return oss;
}

/* Method save() stores the object through the StorageManager */
void VineCopulaFactory::save(Advocate & adv) const
{
  DistributionFactoryImplementation::save(adv);
}

/* Method load() reloads the object from the StorageManager */
void VineCopulaFactory::load(Advocate & adv)
{
  DistributionFactoryImplementation::load(adv);
}


} /* namespace OTVINE */
