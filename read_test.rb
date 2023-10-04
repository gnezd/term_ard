require './term_ard'
require 'pry'
at = ArdTerm.new '/dev/ttyACM0'
puts "Inited"
t0 = Time.now

5.times do
  puts at.cmd "R0-50"
end

puts Time.now - t0

binding.pry
at.close