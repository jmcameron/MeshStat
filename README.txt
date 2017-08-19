MeshStat
========

Version 0.9.0
Copyright (c) 2017
License: GPL 2 or higher

Author: Jonathan M. Cameron, KF6RTA
        jmcameron@gmail.com

This program will display the status of a set of Mesh Nodes on a
periodic basis.

Please send me email if you have difficulties with this program!
(Include which OS and version of OS you're using as well as the
MeshStat version number).


Installation
------------

* Copy the executable anywhere you want
    * Linux executable:  MeshStat
    * Windows executable:  MeshStat.exe

* Create a MeshStat.ini file in the same directory.  See the sample
  version (with commented out settings) in the file 'Sample-MeshStat.ini'
  for examples and descriptions of what can be set.

    * Make sure the 'period' (seconds) is set to a number greater than
      the number of nodes!

    * Adjust 'num_columns' and 'font_size' as you wish.  You may
      need to adjust the other 'pane_*' settings to get the display
      to work out nicely.

    * Make sure to list at least one node in the [Nodes] section

- Run the MeshStat executable

  NOTE: For more than a few nodes, it may take a moment start up the
        first time

- Each operational node should display its status in 4 lines.  If
  you do not see the node name on the first line, it is likely you
  may need to adjust 'pane_width_chars' and 'pane_interline_space'
  to get all on 4 lines to show properly. On Windows this may cause
  periodic beeping when this problem occurs.  There is a brief
  explanation of these parameters in the file 'Sample-MeshStat.ini'.
  You may want to work this out with a smaller set of nodes before
  using a larger list of nodes.

- WARNING: With more than a few nodes, avoid trying to move the
  windows while the nodes are being updated.  It may not be
  responsive and lead to problems that may require restarting the
  programx.

- You can get help from the program by running it on the command
  line like this:

     MeshStat -h
