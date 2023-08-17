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
    @ser.flush
    @ser.puts command
    result = ""
    while true
      temp = @ser.gets
      if temp # Might get bombarded by nil
        #puts "brrrr"
        result += temp
        return result if temp[-1] == "\n"
      end
    end
  end

  def close
    @ser.close
  end
end