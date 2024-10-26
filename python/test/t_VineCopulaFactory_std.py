#!/usr/bin/env python

import openturns as ot
import otvine

factory = otvine.VineCopulaFactory()

ref = ot.ClaytonCopula(2.0)
sample = ref.getSample(1000)
distribution = factory.build(sample)
print(distribution)

for u in sample[:5]:
    print(f"pdf={distribution.computePDF(u)} ref={ref.computePDF(u)}")
    print(f"cdf={distribution.computeCDF(u)} ref={ref.computeCDF(u)}")
realization = distribution.getRealization()
print(realization)

sample = distribution.getSample(1000)
print(sample.computeMean())
