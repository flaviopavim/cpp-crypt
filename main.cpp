#include <string>
#include <locale>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
//
//  base64 encoding and decoding with C++.
//  Version: 1.01.00
//
#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */

string txt="your message here";
string key="your-key";

static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";
static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = ( char_array_4[0] << 2       ) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = 0; j < i; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
string rev(string s) {
  string greeting = s;
  int len = greeting.length();
  int n=len-1;
  for(int i=0;i<(len/2);i++){
    swap(greeting[i],greeting[n]);
    n = n-1;

  }
  return greeting;
}



int indexof(std::string& text, std::string& pattern) {
    std::string::size_type loc = text.find(pattern, 0);
    if(loc != std::string::npos)
    {
        return loc;
    }
    else
    {
        return -1;
    }
}

string cesar(string s, int n, bool rv) {
    string m[2];
    m[0] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    m[1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int sm;
    string r = s;
    for (int a = 0; a <= 1; a++) {
        string mt = m[a];
        int p = indexof(mt,s);
        //std::cout << p;
        if (p >= 0) {
            if (rv == true) {
                sm = p - n;
            } else {
                sm = p + n;
            }
            while (sm >= 52) {
                sm -= 26;
            }
            while (sm < 0) {
                sm += 26;
            }
            r = mt[sm];
        }
    }
    return r;
}

int charVal(string c) {
    string m = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int p = indexof(m,c);
    if (p > 0) {
        return p;
    }
    return 0;
}


string viginere(string s, string k, bool rv) {
    int kl = k.length();
    int cn = 0;
    string r = "";
    for (int i = 0; i < s.length(); i++) {
        if (cn == kl) {
            cn = 0;
        }
        char c=k[cn];
        std::string ss(1, c);
        int int_=charVal(ss);
        string cs="";
        std::string si(1, s[i]);
        cs=cesar(si, int_, rv);
        r += cs;
        cn++;
    }
    return r;
}

string sh(string s, int d) {
	 //std::cout << s;
    int g = 1, l = s.length();
    string ns[l];
    for (int i = 0; i < l; i++) {
        if (g > d) {
            g = 1;
        }
        if (s[i]) {
            ns[g] += s[i];
        }
        g++;
    }
    string r = "";
    for (int a = 1; a <= d; a++) {
        r += ns[a] + "";
    }
    return r;
}
string unsh(string s, int d) {
    int c = 0, a = 0;
    int l = s.length();
    char arr[l];
    for (int i = 0; i < l; i++) {
        if (s[i]) {
            arr[c] = s[i];
        }
        if (c < (l - d)) {
            c += d;
        } else {
            a++;
            c = a;
        }
    }
    string r = "";
    for (int i = 0; i < l; i++) {
        if (arr[i]) {
        	std::string ss(1, arr[i]);
            r += ss + "";
        }
    }
    return r;
}

string b64encode(string s) {
	return base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
}
string b64decode(string s) {
	std::string decoded = base64_decode(s);
	return decoded;
}

string cr(string s) {
    s=b64encode(s);
    s=viginere(s,key,true);
    s=sh(s,3);
    s=rev(s);
    s=sh(s,2);
    s=rev(s);
    s=sh(s,5);
    s=rev(s);
    s=unsh(s,7);
    s=sh(s,5);
    return s;
}

string dc(string s) {
	s=unsh(s,5);
    s=sh(s,7);
    s=rev(s);
    s=unsh(s,5);
    s=rev(s);
    s=unsh(s,2);
    s=rev(s);
    s=unsh(s,3);
    s=viginere(s,key,false);
    s=b64decode(s);
    return s;
}

int main(int argc, char** argv) {
	std::cout <<"Text: ";
	std::cout <<"\n";
	std::cout <<"\n";
	std::cout <<txt;
	std::cout <<"\n";
	std::cout <<"\n";
	std::cout <<"Crypt: ";
	std::cout <<"\n";
	std::cout <<"\n";
	string cr_=cr(txt);
    std::cout <<cr_;
    std::cout <<"\n";
    std::cout <<"\n";
    std::cout <<"Decrypt:";
    std::cout <<"\n";
    std::cout <<"\n";
    std::cout <<dc(cr_);
	return 0;
}
