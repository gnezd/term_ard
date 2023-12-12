# Read the readout from Arduino via serial and plot a rolling plot
require 'serialport'
require 'tk'
require './term_ard'

class PlotContent
  attr_accessor :data, :tkc_objects
  def initialize(tkcanvas)
    @cvs = tkcanvas
    @data = []
    @tkc_objects = []
  end
  
  def update(options = {})
    t0 = options[:t0] if options[:t0]
    pts = options[:pts] if options[:pts]
    frame_size = options[:frame_size] if options[:frame_size]
    
    # Limit number of points
    if pts
      pts = (@data.size < pts) ? @data.size : pts # If there isn't enough data yet
      r = 2
      t0 = @data[-pts][0]
      t_end = @data[-1][0]
      scaling = t_end-t0
      (0..pts-1).each do |i|
        pt = @data[-pts+i]
        offset_pt = [pt[0]-t0, pt[1]]
        projected_pt = [offset_pt[0]/scaling*600, pt[1]]
        if @tkc_objects[i]
          @tkc_objects[i].coords(projected_pt[0]-r, projected_pt[1]-r, projected_pt[0]+r, projected_pt[1]+r)
        else
          @tkc_objects.push TkcOval.new(@cvs, projected_pt[0]-r, projected_pt[1]-r, projected_pt[0]+r, projected_pt[1]+r)
        end
      end
    end
  
  end
end

# Init
r = TkRoot.new {title 'Serial reader'}
lb1 = TkLabel.new(r) {text 'Title'}
cvs = TkCanvas.new(r) {width 600; height 600; pack}
dataset = PlotContent.new(cvs)
t0 = Time.now
ard1=ArdTerm.new '/dev/ttyACM0'

# Display controls
pause_check = TkCheckButton.new(r) {text 'pause'; pack}
frame_size = TkText.new(r) {height 1; pack}


Thread.new do
  t0 = Time.new
  while true
    if pause_check.get_value == '0'
      data = ard1.cmd("R0-10")
      readings = data.split(',,')[0..-2].map {|x| x.to_i}
      reading = 600.0-(readings.sum.to_f / readings.size/1024.0*600.0)
      dataset.data.push [Time.now, reading]
      dataset.update(pts: 30)
      puts reading
      puts dataset.data.last[1]
    else
      # Do nothing
    end
  end
  puts "Dataset accumulated #{dataset.data.size} datapoints"
  puts "along with #{dataset.tkc_objects.size} canvas objects"
end
r.mainloop