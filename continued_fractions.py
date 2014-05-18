"""
FAST HUMAM READABLE APPROXIMATED FRACTION.

Obtain a approximate fraction from a decimal using the continued fractions
theory. Unlike the python module the result can not be exact but a simpler,
and more human readable one.

Examples:
DECIMAL  fraction.Fraction  decimal_to_fraction (maximum error = 0.05)
2.35     47/20              7/3
1.28     32/25              5/4
0.84     21/25              5/6
0.33     33/100             1/3
0.15     3/20               1/7

Robert Oliveira, 2014.05.16
License: Do whatever you want to

REFERENCES
http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.html
"""


def fraction_to_cf(numerator, denominator):
    """fraction to continued fraction in the list format"""
    numerator = int(numerator)
    denominator = int(denominator)
    continued_fraction = list()
    while denominator != 0:
        continued_fraction.append(numerator / denominator)
        numerator, denominator = denominator, numerator % denominator
    return continued_fraction

def cf_to_decimal(cf_list):
    """continued fraction in list format to decimal"""
    decimal = 0.0
    if cf_list:
        for n in reversed(cf_list[1:]):
            decimal = 1.0 / (decimal + n)
        decimal += cf_list[0]
    return decimal

def cf_to_fraction(cf_list):
    """continued fraction in list format to numerator/denominator fraction"""
    numerator = 0
    denominator = 1
    for n in reversed(cf_list[1:]):
        numerator, denominator = denominator, n * denominator + numerator
    numerator = cf_list[0] * denominator + numerator
    return numerator, denominator

def decimal_to_fraction(decimal, max_error=0.05):
    """from decimal to the simpler fraction satisfying the maximum error.
    result in a tuple: (numerator, denominator)"""
    denominator = int(1 / max_error)
    cf = fraction_to_cf(decimal * denominator, denominator)
    print cf
    for n in range(1, len(cf)+1):
        approximated = cf_to_decimal(cf[:n])
        print approximated
        if abs(approximated - decimal) <= max_error:
            return cf_to_fraction(cf[:n])
