//                                               -*- C++ -*-
/**
 *  @brief VineCopulaFactory
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
#include "otvine/VineCopulaFactory.hxx"
#include <openturns/PersistentObjectFactory.hxx>

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
  
  // Eigen::MatrixXd data2 = data;
  
  vinecopulib::Vinecop model(dimension);
  model.select_all(data);
  std::cout << model.str() << std::endl;
  // vinecopulib::Vinecop model(dimension);
  // model.select_families(data);
  // std::cout << model <<std::endl;
  return Distribution();
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
