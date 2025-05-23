#!/usr/bin/env python

import openturns as ot
import openturns.testing as ott
import otvine

factory = otvine.VineCopulaFactory()

ref = ot.ClaytonCopula(2.0)
N = 2500
sample = ref.getSample(N)
distribution = factory.build(sample)
print(distribution)
assert "Clayton" in str(distribution)
for u in sample[:5]:
    ott.assert_almost_equal(distribution.computePDF(u), ref.computePDF(u), 1e-2, 1e-2)
    ott.assert_almost_equal(distribution.computeCDF(u), ref.computeCDF(u), 1e-2, 1e-2)
realization = distribution.getRealization()
print(realization)

# check get the same distributions after inference
factory.setNative(True)

R = ot.CorrelationMatrix(2)
R[1, 0] = 0.25
copula = ot.NormalCopula(R)
sample = copula.getSample(N)
distribution = factory.build(sample)
print(distribution)
assert distribution.getName() == "NormalCopula"

copula = ot.GumbelCopula()
for rotation in [0, 90, 180, 270]:
    rotated = otvine.RotatedCopula(copula, rotation)
    sample = rotated.getSample(N)
    distribution = factory.build(sample)
    print(distribution)
    assert "GumbelCopula" in str(distribution)
    if rotation > 0:
        assert f"rotation={rotation}" in str(distribution)

copula = ot.ClaytonCopula(2.0)
for rotation in [0, 90, 180, 270]:
    rotated = otvine.RotatedCopula(copula, rotation)
    sample = rotated.getSample(N)
    distribution = factory.build(sample)
    print(distribution)
    assert "ClaytonCopula" in str(distribution)
    if rotation > 0:
        assert f"rotation={rotation}" in str(distribution)
