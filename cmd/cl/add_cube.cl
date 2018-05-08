for (i = 0; i < 10; ++i)
  x = 2*rrand()
  y = 2*rrand()
  z = 2 + rrand()

  xa = 360*rrand()
  ya = 360*rrand()
  za = 360*rrand()

  raytrace::add_cube -size 0.5 -color "white" -translate [x,y,z] -rotate [xa,ya,za] -reflect 0.9
endfor

raytrace::add_light -position [0,0,1] -color "red"
raytrace::add_light -position [1,1,1] -color "green"

raytrace::render
