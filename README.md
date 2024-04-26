# Responsive GUI in QT

The QT Framework has the ability to create flexible and responsive Graphical User Interfaces (GUI) through its Widget Sizing Policy. This example shows how you have several widgets on your layout and control the responsiveness of each.

Here I have a List Widget on the left and a Table Widget on the right. The specifications for this design were that the List Widget remained fixed in horizontal width whilst being free to grow vertically if required. In contrast, the Table widget would be allowed to grow both in the horizontal and vertical planes.

In addition, I wanted the behaviour of the Table columns to also be responsive and grow uniformly with the Widget itself. However I also wanted to show how you can implement a custom width for any particular column and have it remained fixed whilst the others still continue to be responsive. This is implemented by overriding and handling the resizeEvent() method from the MainWindow class and using it to dynamically resize the columns.

https://github.com/GitDhamani/ResponsiveGUI/assets/111576658/d37a98a7-e9b5-4394-b4cd-1a001a634635
![ResponsiveGUI](https://github.com/GitDhamani/ResponsiveGUI/assets/111576658/49e86746-1dea-4ff2-a14d-780172145fe8)










