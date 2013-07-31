FacebookParser
===================

This was a programming assignment that I completed in Data Structures in the Spring of 2013 at UF. I utilized this parser: https://github.com/udp/json-parser. To view the initial assignment as well as the instructions given to me for the project, please view the file "AssignmentPage.htm".  

In order to use this program, you must generate a list of facebook friends with information. Instructions to do so are on the page "AssignmentPage.htm",but I will restate them here:

To access this list, you will need to log on to Facebook and enter the following URL into a browser window. You will need to somehow discover your access token (it's somewhere on the Developers site - you'll probably have to pull it off the URL from a link - I found it on the News Feed link at this address https://developers.facebook.com/docs/reference/api/search/) (UPDATE: Not many people have locations, so just use hometown instead): https://graph.facebook.com/me/friends?fields=birthday,first_name,last_name,hometown&limit=1000&access_token=<put your access token here>

After you have aquired this list, please save it as a text file with the name "facebook.txt", in your program's directory. 

Thank you,
Samuel Sewall