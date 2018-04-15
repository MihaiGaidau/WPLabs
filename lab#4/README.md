# Windows Programming Laboratory Work #4
## Subject
_Windows Timer. Animation._

## Bonus Objectives

- [x] Increase and decrease animation speed using mouse wheel (2 pt)
- [x] Solve flickering problem (2 pt) please describe in your readme/report how you did it
- [x] Add animated objects which interact with each other (2-6 pt), ex.:
    - Few balls which have different velocity and moving angles. In order to get max points, add balls with mouse, make balls to change color on interaction and any other things that will show your engineering spirit
    - Any other interesting and reach in animation application
- [x] Animate a Nyan Cat that leaves a rainbow tail (Math.floor(+35% for task with interacting objects))

## Result
Implementation Analysis<br>
I chose to perform this laboratory work in c++ because I found  a lot of functions that made me easy to understand how work with animation in
windows application and how to create something interactive.<br>
So , starting the application the animation started and by clicking mouse in the center will appear the balls of different velocities.
When balls hit the wall of the action surface, they change the color. All the actions that happen are against time. Also moving the mouse 
wheel the speed of the animation should increase.<br>
### How solve the flicker problem?<br>
This problem was solved by the double buffer. Solving this problem I can avoid the bottlenecks, 
for example, with graphics, double buffering can be used to show one image or frame while a separate frame is being buffered to be shown next.
This method makes animations and games look more realistic than the same done in a single buffer mode.

  ## Conclusion
During this laboratory work I have learned how to made animations how to redraw background to show this.Also , I have learned about interactions
between objects and how to change their properties , for example : color , dimensions. Also , I understand about animations and transitions
that this are effective and improved usability, smoothness and flow, and the perception of quality, without harming performance significantly.
