//                                               -*- C++ -*-
/**
 *  @brief RotatedCopula
 *
 *  Copyright 2005-2026 Airbus-EDF-IMACS-ONERA-Phimeca
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
#ifndef OTVINE_ROTATEDCOPULA_HXX
#define OTVINE_ROTATEDCOPULA_HXX

#include <openturns/DistributionImplementation.hxx>
#include <openturns/Distribution.hxx>

#include "otvine/otvineprivate.hxx"

namespace OTVINE
{

/**
 * @class RotatedCopula
 *
 * RotatedCopula is some vinecopulafactory type to illustrate how to add some classes in OpenTURNS
 */
class OTVINE_API RotatedCopula
  : public OT::DistributionImplementation
{
  CLASSNAME

public:
  /** Default constructor */
  RotatedCopula();
  
  explicit RotatedCopula(const OT::Distribution & copula, const OT::SignedInteger rotation = 90);

  /** Virtual constructor method */
  RotatedCopula * clone() const override;

  OT::Bool operator ==(const RotatedCopula & other) const;
protected:
  OT::Bool equals(const DistributionImplementation & other) const override;
public:

  /** String converter */
  OT::String __repr__() const override;
  OT::String __str__(const OT::String & offset = "") const override;

  /** Get one realization of the distribution */
  OT::Point getRealization() const override;

  /** Get the DDF of the distribution */
  using OT::DistributionImplementation::computeDDF;
  OT::Point computeDDF(const OT::Point & point) const override;

  /** Get the PDF of the distribution */
  using OT::DistributionImplementation::computePDF;
  OT::Scalar computePDF(const OT::Point & point) const override;

  /** Get the CDF of the distribution */
  using OT::DistributionImplementation::computeCDF;
  OT::Scalar computeCDF(const OT::Point & point) const override;

  /** Get the PDFGradient of the distribution */
  using OT::DistributionImplementation::computePDFGradient;
  OT::Point computePDFGradient(const OT::Point & point) const override;

  /** Get the CDFGradient of the distribution */
  using OT::DistributionImplementation::computeCDFGradient;
  OT::Point computeCDFGradient(const OT::Point & point) const override;

  /** Compute the CDF of Xi | X1, ..., Xi-1. x = Xi, y = (X1,...,Xi-1) */
  using OT::DistributionImplementation::computeConditionalCDF;
  OT::Scalar computeConditionalCDF(const OT::Scalar x, const OT::Point & y) const override;

  /** Compute the quantile of Xi | X1, ..., Xi-1, i.e. x such that CDF(x|y) = q with x = Xi, y = (X1,...,Xi-1) */
  using OT::DistributionImplementation::computeConditionalQuantile;
  OT::Scalar computeConditionalQuantile(const OT::Scalar q, const OT::Point & y) const override;

  /** Parameters value accessors */
  void setParameter(const OT::Point & parameter) override;
  OT::Point getParameter() const override;

  /** Parameters description accessor */
  OT::Description getParameterDescription() const override;

  /** Check if the distribution is continuous */
  OT::Bool isContinuous() const override;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

  OT::UnsignedInteger getRotation() const;
  OT::Distribution getCopula() const override;

private:
  OT::Point rotate(const OT::Point & x, const OT::Bool inverse = false) const;
  
  OT::Distribution copula_;
  OT::UnsignedInteger rotation_ = 0;

}; /* class RotatedCopula */

} /* namespace OTVINE */

#endif /* OTVINE_ROTATEDCOPULA_HXX */
