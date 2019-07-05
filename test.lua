require "testing"

print("TESTING ADD")

local sum = EPlugin.addNumbers(100, 666)

print("100 + 666 = " .. sum)

print("TESTING FACTORIAL")

local fact = EPlugin.factorial(10)
print("10! = " .. fact)

print("------------")
