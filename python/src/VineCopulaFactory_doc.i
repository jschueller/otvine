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

