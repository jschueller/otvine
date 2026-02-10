"""
Estimate a Vine copula
======================
"""

# %%
import openturns as ot
import otvine

# %%
# Generate a copula sample
sample = ot.ClaytonCopula().getSample(1000)

# %%
# Estimate a Vine copula
factory = otvine.VineCopulaFactory()
distribution = factory.build(sample)
