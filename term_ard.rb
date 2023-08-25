# Wrap-up some operations of the Arduino terminal
require 'serialport'
class ArdTerm
  attr_accessor :ser # Expose serial for debugging
  def initialize(tty_path='/dev/ttyUSB0', bd_rate = 9600)
    @ser = SerialPort.new tty_path, bd_rate, 8 # Will the number of data bits ever be different from 8?
    @ser.read_timeout=10 # We have no patience here
    true
  end

  # Send command and return results
  def cmd(command)
    puts "---before cmd is sent---"
    puts read # Flushing RX buffer
    puts "-----"
    
    @ser.flush
    @ser.puts command
    read(true)
  end

  def read(exp = false)
    result = ""
    empty_count = 0
    if exp == true # Expecting return
      while (temp = @ser.read) && (temp == "")
      end
      puts temp
      result += temp
      sleep 0.01
    end
    while (temp = @ser.read)
      if temp == ""
        empty_count +=1
        result += '-'
      end
      result += temp
      break if empty_count > 100
    end
    result
  end

  def close
    @ser.close
  end
end