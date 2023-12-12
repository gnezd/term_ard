require './term_ard'
require 'pry'
at = ArdTerm.new '/dev/ttyACM0'
puts "Inited"

t0 = Time.now
5.times do
  at.cmd "R0-50"
end

puts "5x50: #{Time.now - t0}"

t0 = Time.now
10.times do
  at.cmd "R0-25"
end
puts "10x25: #{Time.now - t0}"

binding.pry
at.close