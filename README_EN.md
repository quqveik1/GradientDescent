# GradientDescent
This program allows you to observe the root-finding process. Coefficients are adjusted for equations of the form \( k \sin(bx) \).

1) The original graph is plotted in blue at the top, with noise and coefficients \( k = 5, b = 7 \).
2) The graph guessed by the program is in red.
3) The graph plotted in green is based on the coefficients you choose.

# What's the Chart at the Bottom?
The bottom chart represents the root-mean-square deviation of the function with coefficients corresponding to the point, i.e., \( K \) is on the x-axis, \( B \) is on the y-axis. The color indicates the deviation: blue for the minimum and red for the maximum.

# What is Root-Mean-Square?
Root-mean-square is the sum of the squares of the differences between the original function value and the function value at the point with coefficients.

# How to Interact with the Program?
Left mouse click on the bottom graph: Choose coefficients based on which a graph will be plotted in green at the top.
Right mouse click on the bottom graph: Perform gradient descent from the point to the optimal coefficients.

# Example:
![image](https://user-images.githubusercontent.com/64206443/233839716-fbb25ffc-4e41-42d0-b66f-404832f33996.png)

# Technical Features
Runs on a [custom graphics library](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP).
The program utilizes 4 threads:
1) The main graphical thread for window message handling
2) A thread for plotting the top graph
3) A thread for calculating the root-mean-square deviation points
4) A gradient descent thread

------------------------------------------------------
# Installation
To run the program, you need to download its compiled version from the releases tab [here](https://github.com/quqveik1/GradientDescent/releases/latest).
Ignore antivirus warnings saying the file contains a virus.

In the dialog box, click "More Info" and then choose "Run Anyway".

![Installation Warning](https://user-images.githubusercontent.com/64206443/182945554-ed4d18c6-a25d-4d0d-a331-e268643b3031.png)
