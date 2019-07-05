require "testing"

print("TESTING ADD")

local sum = EPlugin.addNumbers(100, 666)

print("100 + 666 = " .. sum)

print("TESTING FACTORIAL")

local fact = EPlugin.factorial(10)
print("10! = " .. fact)

print("TESTING VECTOR DOT")
local a = Vector(120, 0, 11)
local b = Vector(2, 0, 33)

local dot = EPlugin.dot(a, b)

print("dot(Vector(120, 0, 11), Vector(2, 0, 33)) = " .. dot)

print("------------")
