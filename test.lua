require "testing"

local function dproduct(a, b)
    local n = 0
    
    n = n + (a.x * b.x)
    n = n + (a.y * b.y)
    n = n + (a.z * b.z)

    return n
end

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

print("Starting benchmark")

local samples = 10000000

print("benchmarking lua code")

-- # Lua Benchmark #
local l_start = os.time()
-- Lua dot product
for i = 0, samples, 1 do
    local d = dproduct(a, b)
end
local l_end = os.time()
-- ######

print("benchmarking c code")

-- # C Benchmark #
local c_start = os.time()
-- C dot product
for i = 0, samples, 1 do
    local d = EPlugin.dot(a, b)
end
local c_end = os.time()
-- ######

local l_ms = ((l_end - l_start)  / samples) * 1000
local c_ms = ((c_end - c_start) / samples) * 1000

print("Lua dot product took " .. l_ms .. "ms on average")
print("C dot product took " .. c_ms .. "ms on average")

