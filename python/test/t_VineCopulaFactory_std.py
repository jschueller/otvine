#!/usr/bin/env python

import openturns as ot
import otvine

factory = otvine.VineCopulaFactory()

sample = ot.ClaytonCopula().getSample(1000)
distribution = factory.build(sample)
print(distribution)