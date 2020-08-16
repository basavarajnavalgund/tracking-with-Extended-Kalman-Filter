import pandas as pd

#read .txt file and assigned name to each columns
df = pd.read_table('output1.txt', delim_whitespace=True, names=['est_px','est_py','est_vx','est_vy','meas_px','meas_py','gt_px','gt_py','gt_vx','gt_vy'])

"""
print("Std. Deviation of Estimated values")
print(df.loc[:,"est_px"].std())
print(df.loc[:,"est_py"].std())
print(df.loc[:,"est_vx"].std())
print(df.loc[:,"est_vy"].std())
print()

print("Std. Deviation of Measured values")
print(df.loc[:,"meas_px"].std())
print(df.loc[:,"meas_py"].std())
print()

print("Std. Deviation of Ground_truth values")
print(df.loc[:,"gt_px"].std())
print(df.loc[:,"gt_py"].std())
print(df.loc[:,"gt_vx"].std())
print(df.loc[:,"gt_vy"].std())

"""

#calculates std.deviation of each column
a=df.std(axis=0)
b=df.mean(axis=0)
print(a)
print(b)
