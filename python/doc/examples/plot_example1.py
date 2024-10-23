"""
Example 1: Axial stressed beam
==============================
"""

# %%
# This example is a simple beam, restrained at one side and stressed by a traction load F at the other side.
#
# Inputs:
#
#  - F, Traction load, Normal(75e3, 5e3)
#  - :math:`sigma`, Axial stress, LogNormal(300, 30)
#  - D, diameter, 20.0
#
# Output: Primary energy savings :math:`G`
#
# .. math::
#
#     G = \sigma_e -\frac{F}{\pi \frac{D^2}{4} }
#

# %%
import openturns as ot
import otvine

a = otvine.VineCopulaFactory()
p = ot.Point([2, 3])
squared_p = a.square(p)
print(squared_p)
