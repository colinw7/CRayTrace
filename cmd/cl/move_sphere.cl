set angle_type degrees

xc = 0.5
yc = 0.5
r  = 0.4

x1 = xc + r
y1 = yc
z  = 2

raytrace::add_sphere -id "sphere" -radius 0.3 -color "white" -translate [x1,y1,z]

raytrace::add_light -position [0,0,1] -color "red"
raytrace::add_light -position [1,1,1] -color "green"

for (i = 0; i < 360; i += 5)
  x2 = xc + r*cos(i)
  y2 = yc + r*sin(i)

  dx = x2 - x1
  dy = y2 - y1

  raytrace::translate_shape -id "sphere" -delta [dx,dy,0]

  raytrace::render

  x1 = x2
  y1 = y2
endfor
