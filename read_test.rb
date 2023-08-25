require './term_ard'
at = ArdTerm.new '/dev/ttyACM0'

puts at.cmd "RRR"
at.close