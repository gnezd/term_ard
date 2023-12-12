# Wrap-up some operations of the Arduino terminal
require 'serialport'
class ArdTerm
  attr_accessor :ser # Expose serial for debugging
  def initialize(tty_path='/dev/ttyACM0', bd_rate = 19200)
    @ser = SerialPort.new tty_path, bd_rate, 8 # Will the number of data bits ever be different from 8?
    @ser.read_timeout=10 # We have no patience here
    sleep 0.01
    message = cmd('I')
    raise "Initiation failed, echo not received" unless message == 'OK'
  end

  # Send command and return results
  def cmd(command)
    @ser.puts command
    result = read(true)
    @ser.flush
    result
  end

  def read(exp = false, read_delay=0)
    result = ""
    empty_count = 0
    if exp == true # Expecting return
      while (temp = @ser.getbyte) != 2 # Identify and chop off STX(incl)
        #puts "Waiting for transmission..."
        #sleep read_delay
      end
      length = @ser.getbyte
      while (temp = @ser.getbyte) != 3
        #puts temp
        #puts "transmission: #{temp}"
        result += "%c" % temp if temp
        sleep read_delay
      end
      puts "Length expected to be #{length} but found to be #{result.size}" unless result.size == length
    else
      while (temp = @ser.read)
        if temp == ""
          empty_count +=1
          result += '-'
        end
        result += temp
        break if empty_count > 100
      end
    end
    result
  end

  def close
    @ser.close
  end
end