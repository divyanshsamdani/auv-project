# auv-project

TASK - 1 :- 
    
    
    
    
    
    It contains beginner_tutorials package. Add this directory to your src directory in your ros workspace directory.
    Open the terminal and move into your workspace folder and do catkin_make(to build your packages and generate all executables and makefiles)
    open another terminal, then source it your devel folder.
    then use rosrun to start the talker node in beginner_tutorials package(also give the integer value from the command line itself), which will publish the value to the chatter topic (eg:- "$rosrun beginner_tutorials talker 5",will publish 5)
    then similarly start the listener node which will subscribe to chatter topic to receive the value.
    
    Also there is practice.cpp file. open a terminal , "$ make practice" , to compile, and ./practice to execute and see the output.
    
    

TASK - 2 :-
    
      build the actionlib_tutorials package same as above.
      in the new terminals rosrun server node and client node (eg for server:- $rosrun actionlib_tutorials newton_server)
      also along with that run feedack and result node using rostopic to see the output.( eg:- $rostopic echo newton/result)
      


PS :- when using ros, source every new terminal you open .
     
