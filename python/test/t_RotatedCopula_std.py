#!/usr/bin/env python

import openturns as ot
import openturns.testing as ott
import otvine

copula = ot.GumbelCopula()

for rotation in [0, 90, 180, 270]:
    rotated = otvine.RotatedCopula(copula, rotation)

    print(rotated)
    print(repr(rotated))
    assert rotated.isContinuous() == copula.isContinuous()
    assert rotated.getParameter() == copula.getParameter()
    assert rotated.getParameterDescription() == copula.getParameterDescription()

    _ = ot.RandomGenerator.Generate()

    ot.Log.Show(ot.Log.TRACE)
    validation = ott.DistributionValidation(rotated)
    validation.run()
