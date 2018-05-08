set angle_type degrees

xc = 0.5
yc = 0.5
r  = 0.4

x1 = xc + r
y1 = yc

raytrace::add_sphere -id "sphere" -radius 0.5 -color "white" -translate [0.5,0.5,2]

raytrace::add_light -id "light1" -position [0,0,1] -color "red"
raytrace::add_light -id "light2" -position [1,1,1] -color "green"

raytrace::move_camera -position [x1,y1,-1]

for (i = 0; i < 360; i += 5)
  x2 = xc + r*cos(i)
  y2 = yc + r*sin(i)

  dx = x2 - x1
  dy = y2 - y1

  raytrace::move_camera -delta [dx,dy,0]

  raytrace::render

  x1 = x2
  y1 = y2
endfor
