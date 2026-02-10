%feature("docstring") OTVINE::VineCopulaFactory
"Estimator for R-vine copulas.

Examples
--------
>>> import otvine
>>> import openturns as ot
>>> sample = ot.ClaytonCopula().getSample(100)
>>> factory = otvine.VineCopulaFactory()
>>> distribution = factory.build(sample)

Notes
-----
https://www.math.cit.tum.de/math/forschung/gruppen/statistics/vine-copula-models/
"

// ---------------------------------------------------------------------

%feature("docstring") OTVINE::VineCopulaFactory::setNative
"Native distributions flag accessor.

Parameters
----------
native : bool
    Whether to use only known parametric copulas."