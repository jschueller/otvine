"""
Create a rotated copula
=======================
"""

# %%
import openturns as ot
import openturns.viewer as otv
import otvine

# %%
# Create a copula
copula = ot.GumbelCopula()
graph = copula.drawPDF()
graph.setTitle('GumbelCopula PDF 0 deg')
view = otv.View(graph)

# %%
# Rotate the copula at 90 degrees
rotated_90 = otvine.RotatedCopula(copula, 90)
graph = rotated_90.drawPDF()
graph.setTitle('GumbelCopula PDF 90 deg')
view = otv.View(graph)

# %%
# Rotate the copula at 90 degrees
rotated_180 = otvine.RotatedCopula(copula, 180)
graph = rotated_180.drawPDF()
graph.setTitle('GumbelCopula PDF 180 deg')
view = otv.View(graph)

# %%
# Rotate the copula at 90 degrees
rotated_270 = otvine.RotatedCopula(copula, 270)
graph = rotated_270.drawPDF()
graph.setTitle('GumbelCopula PDF 270 deg')
view = otv.View(graph)

# %%
otv.View.ShowAll()
