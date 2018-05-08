proc createGUI { } {
  set frame .frame

  frame $frame

  #----

  set canvas $frame.canvas

  CTclRayTracerCanvas $canvas

  pack $canvas -side top -anchor w -fill both -expand true

  focus $canvas

  $canvas loadFile test.data

  #----

  pack $frame -side left -fill both -expand true
}

createGUI
