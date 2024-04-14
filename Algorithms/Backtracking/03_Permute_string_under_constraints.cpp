#include<iostream>

using namespace std;

bool no_AB_String(string str, int i, int l, int r)
{
	// l -> current charcter that is swapped
	// i -> character that the current is swapped with
	// l-1 -> previous to current
	// If previous character is 'A', current one shouldn't be 'B'
	if(l>0 && str[l-1]=='A' && str[i]=='B')
		return false;

	// The above condition checks for the presence of "AB" substring throughout the entire string except the last two letters since when the previous check is for (l-1)th character and lth character (after swapping) being "AB". Thus, for l=r-1, (r-2)th and (r-1)th characters are checked against "AB". Then, when l==r, the string is just simply printed in the permute function w/o checking if if (r-1)th and rth characters form "AB". So, we need to perform that check when l=r-1 itself.
	// CASE I: i!=l => i=r and l=r-1 => We need to check for, str[l]=='A' && str[i]=='B'	[Swapping would be b/w the last elements i.e., "BA" becomes "AB"]
	// CASE II: i==l => i=l=r-1 => We need to check for, str[i]==str[r-1]==str[l]=='A' && str[i]=='B'	[Swapping would be, of the second last element with itself i.e., "AB" remains "AB"]
	if( r==l+1 && ((str[i]=='A' && str[l]=='B') || (i==l && str[l]=='A' && str[r]=='B')))
		return false;
	
	return true;
}

void permute_without_AB(string str, int l, int r)
{
	// l -> Index of the current string position for which we're fixing a character
	// i -> Index of character that will be swapped with str[l]

	// l==r implies we've reached the end of the string (str is a solution now)
	if(l==r)
		cout<<str<<" ";		// We could've also simply used if(str.find("AB")) here but that would be too inefficent. With our solution, we can avoid using the find() function [usually linear complexity]. Additionally, we can discard travelling through the solution subtrees as soon as we find "AB" in the string.
	else {
		for(int i=l; i<=r; i++) {
			// Check that there'll be no "AB" substring in str if we swap(str[i],str]l)
			if(no_AB_String(str, i, l, r)) {
				swap(str[l], str[i]);
				permute_without_AB(str, l+1, r);	// Each time this function executes (and increases l by 1), we have fixed one more character in the string. Since this is done in DFS fashion, we'll keep going from l=0 to l=r.
				swap(str[l], str[i]);	// Backtrack in the solution tree by putting back the string as it was before and continue. By the time we reach this step, we would have already printed all the allowed string permutations (if any) we can get on swapping str[l] & str[i].
			}
		}
	}
}

int main()
{
	string str;
	cin>>str;

	// CONSTRAINT -> There should be no "AB" substring in the permutation
	permute_without_AB(str,0,str.size()-1);

	return 0;
}