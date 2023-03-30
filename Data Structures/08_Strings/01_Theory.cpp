#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    string name = "Walter White";
    // To get a substring of string 'str'.
    // str.substr(start_index, size_of_substring);
    cout<<name.substr(4,7)<<"\n\n";

    // To find a substring in a string 'str'.
    // str::npos is returned if not found.
    // str.find("Substring to be found");
    cout<<name.find("hit")<<"\n";
    cout<<name.find("Kal")<<"\n\n";

    // Stops reading once it finds a whitespace.
    cin>>name;
    cout<<name<<"\n\n";

    // Continues reading until the enter key is pressed.
    // getline(cin, str, character_to_stop_reading_the_input_at_OPTIONAL)
    // If the optional paramter (stop character) is not there in the input passed, it will keep receiving the input, no matter how many times you press enter.
    // If the string passed in the previous 'cin' function has a whitespace in between, cin will read only the part before the whitespace and the rest will be read by getline (given that they are written consecutively).
    string name2;
    getline(cin, name2);
    cout<<name2<<"\n";
    getline(cin, name2, 'i');
    cout<<name2<<"\n\n";

    // Alternative way to iterate through a string
    for(char x:name)
        cout<<x;
    cout<<"\n";
    for(char x:name2)
        cout<<x;
    
    // Reverse Function [#include<algorithm>]
    reverse(name.begin(), name.end());
    cout<<"\n"<<name<<"\n";

    // In case of the pattern (size m) having all characters as distinct, irrespective of the text (size n), we can perform the patter searching problem in O(n) as you can skip the part that did match.
    
    return 0;
}