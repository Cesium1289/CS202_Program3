
# Programming Assignments #4 and 5 CS 202 Programming Systems

## For This Program
With both programs #4 and #5 you will be implementing your solutions using
Java. Your goal must be to develop an object-oriented solution but this time
implement it in Java. Make sure that your OO Design is not centered around
your data structures – your data structures support the design but shouldn’t be
the primary emphasis of your design. You may use Eclipse or IntelliJ to develop
your software. Your Java programs must follow these rules:

•No public or friendly fields (data members) *** NONE!!!***

• No friendly methods (member functions)

• Yes, you SHOULD use the string class!

• Limit your use of static methods – these should be restricted to just
utility functions and main

• Use an inheritance hierarchy using “extends”; there must be a
minimum of 5 classes with 3 of them in a hierarchy. These should not
be isolated to just your data structures.

• The application that USES the hierarchy must be in a class on its
own. Or, it could be part of a hierarchy, so think about that.
• Create at least one abstract base class

• Implement at least one constructor with arguments

• Implement at least two functions using function overloading
between classes and experiment with the way function overloading
works in Java. ***Write about this.

• Implement dynamic binding and experiment with how it works in
Java. Prove to yourself that the functions are being overridden
versus overloaded. ***Write about this

• Try out the super keyword in invoking a base class’ constructor.
This is what we use instead of an initialization list. ***Write about this in
your

• There no limit to the number of files allowed for this assignment.

## Data Structures ##

In these last two programs, you must implement two data structures:
1. Program 4: A playlist implemented as an array of linear linked lists
2. Program 5

        a. Implement a tree where each node has a playlist of items.

        b. If you have already implemented a balanced tree in program #3:
        Implement a Binary Search tree, with insert, display, retrieve,
        retrieve, remove an individual item, and remove all; the algorithms
        must be implemented recursively.

        c. If you have not yet implemented a balanced tree, then one is
        required for this assignment. You are not required to implement a
        individual remove function for a balanced tree
        
The required data structures specified in the assignment must be your own
implementation: as in BST (or balanced tree) and linear linked lists. Once you
meet the basic requirements of the assignment, you are allowed to use libraries
for any subsequent data structures

## Program Requirements ##
In my “spare” time, I am working on creating truly “online” classes. These are
not the same as remote classes because everything needs to be distributed
automatically during the week. There isn’t a time when the teacher has
synchronous discussions with the students. Part of this work involves creating
multitudes of short videos that are in a playlist. For example, in the second week
of CS162, we have around 12 short 6-10 minute videos that need to be played in a
particular order. Luckily the concept of a playlist allows for one video to feed
into the next, and so on. The trouble I am having is in the use of the PSU website
that really doesn’t support a natural way of putting playlists together. I could
really use some help!

For this programming assignment, you have been “hired” to design a system
that would allow media to be managed by your software once uploaded.
Example operations expected would be to upload media, close caption the
media, remove the media, publish it for general viewing, or publish it for a
specific class. Videos that I upload can have comments, attachments, description,
allow for users to post comments, and much more. Authors can look at the analytics of how often these videos have been watched (or re-watched). In addition, quiz questions can be added to media. For this assignment, I expect at
least 4 features to be supported for this project in addition to allowing quiz
questions to be added to the videos. Think of a video with a quiz option is a
media object plus more.

Each course can have multiple playlists of these media available for the viewers
to step through. It would be nice if the playlists themselves were ordered
(something it doesn’t look like PSU’s site supports).

Try to make this a user friendly environment and of course at the same time as
making it object oriented. In Program #4 you are to build the part of the
application that creates one playlist. In Program #5, allow for classes to be
supported each with multiple playlists!

Your job is to come up with a design of an OO framework that will support an
application. The key is to make sure to solve this problem using Object Oriented
methodologies with dynamic binding and function overloading. The use of
external data file(s) is necessary!
