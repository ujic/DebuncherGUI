The code make inverse integral distribution function for the extraction/ejection of the ions from the debuncher
read, A. Lapierre, Time-dependent potential functions to stretch the time distributions of ion pulses ejected from EBIST, Canadian Journal of Physics, 2017, 95(4): 361-369, https://doi.org/10.1139/cjp-2016-0716

The Dictionary file must be read before the Makefile started. (read Dictionary_Build.README)

The file must be indicated as open, then the historgram adjusted (in ms). If the kick is present it can start from 1 ms. Number of bins effectively defines the resolution and the averaging of the inverse function. 

The BCG doesn't work for now.

if Draw is on it can draw each bunch with given time step (if it's negative, it will show the next bunch). It is better that the Draw check button is uncheck during the Calculation of inverse function "Calculate Inv. func.".

The offset and ending ramp voltage must be same as the one which were use during the linear ramp extraction. 




