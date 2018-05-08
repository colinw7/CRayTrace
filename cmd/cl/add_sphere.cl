for (i = 0; i < 10; ++i)
  x = 2*rrand()
  y = 2*rrand()
  z = 2 + rrand()

  raytrace::add_sphere -radius 0.4 -color "white" -translate [x,y,z] -refract 0.8
endfor

raytrace::add_light -position [0,0,1] -color "red"
raytrace::add_light -position [1,1,1] -color "green"

raytrace::render
