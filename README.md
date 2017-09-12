MeshStat
========

Amateur Radio Mesh Network Status Monitor

Version 0.10.0
Copyright (c) 2017
License: GPL 2 or higher

Author: Jonathan M. Cameron, KF6RTA
        jmcameron@gmail.com

This program will display the status of a set of Mesh Nodes on a
periodic basis.

Please send me email if you have difficulties with this program!
(Include which OS and version of OS you're using as well as the
MeshStat version number).


Installation and Set Up
-----------------------

* Copy the executable anywhere you want
    * Linux executable:  MeshStat
    * Windows executable:  MeshStat.exe

- You can get help from the program by running it on the command
  line like this:

     MeshStat -h

- Create a MeshStat.ini file in the same directory.  See the sample
  version (with commented out settings) in the file 'Sample-MeshStat.ini'
  for examples and descriptions of what can be set.

    * Make sure the 'period' (seconds) is set to a number greater than
      the number of nodes!

    * Adjust 'num_columns' and 'font_size' as you wish.  You may
      need to adjust the other 'pane_*' settings to get the display
      to work out nicely.

    * Make sure to list at least one node in the [Nodes] section

- You may also specify an alternate MeshStat config file on the command
  line.

- Run the MeshStat executable!

- Each operational node should display its status in 4 lines.  If
  you do not see the node name on the first line, it is likely you
  may need to adjust 'pane_width_chars' and 'pane_interline_space'
  to get all on 4 lines to show properly. On Windows this may cause
  periodic beeping when this problem occurs.  There is a brief
  explanation of these parameters in the file 'Sample-MeshStat.ini'.
  You may want to work this out with a smaller set of nodes before
  using a larger list of nodes.

- If you're having trouble getting all four lines to display, follow
  this procedure:
    - Chose the font_size you want (eg, 10, 11, 12)
    - Choose a small size for 'pane_width_chars', such as 20.
    - Run the program and enlarge the display until all panes
      display their content in 4 lines.
    - Under the *Help* menu look at the *About* page and notice the
      current width of the panes.  Change the 'pane_width_chars' to
      this value.  In the future when you run the program, the
      display should be wide enough. 
    - If all four lines are still not displaying, increase
      'pane_interline_space' (pixel by pixel) until the fourth line
      displays properly.  Or set 'pane_hight_lines' to 5.

- WARNING: With more than a few nodes, avoid trying to move the
  windows while the nodes are being updated.  It may not be
  responsive and lead to problems that may require restarting the
  program.

- If you have a lot of nodes, there is a 'one-line' mode that displays only
  one status line per node:

     - add this setting to the [Settings] section your config file:

          display_mode = one-line

     - Note that in this mode, the 'pane_height_lines' setting is ignored

     - You can move our mouse over any node line to see details for that node.

     - Here is a procedure to help optimize the display with a large number of
       nodes:
          - Set config settings:
               display_mode = one-line
               num_columns = 6          ; or as large as your monitor supports
	       font_size = 9
               pane_width_chars = 10
          - You should see gap on the left and right edges of each
            node cell, but the node display text will be truncated.
          - Resize the window or increase 'pane_width_chars' until
	    the whole MeshStat program window reaches the width of
	    the monitor OR until the gap on each side of each node
	    cell disappears.  The decrease 'pane_width_chars' by
	    one.
          - If you do not get the full name of most of your nodes
            displayed, Reduce the 'font_size' and repeat the process
  
- If you have several differnt sets of nodes to monitor (eg, for the
  different frequency bands), you can specify an arbitrarily named
  MeshStat config file on the command line:

    MeshStat myconfig.ini

  So you can set up several shortcuts, each specifying a different config
  file.  On MS Windows modify the "Target" item for each to insert the config
  file name after the MeshStat.exe executable.  If the config file is in the
  same directory as the MeshStat.exe executable program, you do not need to
  specify the full path, only the filename.
