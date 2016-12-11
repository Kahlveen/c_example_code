#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pcre.h>
int main()
{
	char * source = "This is something\nTo: baboonKing!@%!$#21231\nThirdField: Some other stuff\nFrom: MonkeyKing3109@#$%\nFourthField: mfownfowfef";
	char * regexString = "^to:(.*)$";

	//PCRE fields
	pcre* compiled_regex;
	pcre_extra* study_val;
	int retval, err_offset;
	int substr_offset[30];	//Must be a multiple of 3
	const char* err;
	const char*	match;

	int pcre_compile_options = PCRE_CASELESS | PCRE_MULTILINE | PCRE_NEWLINE_ANYCRLF;
	compiled_regex = pcre_compile(regexString,pcre_compile_options, &err, &err_offset, NULL);

	//pcre_compile returns NULL on error, and sets err_offset & err
	if (compiled_regex == NULL){
		printf("ERROR :: Could not compile '%s': %s\n",regexString, err);
		exit(1);
	}

	//Optimize the regex
	study_val = pcre_study(compiled_regex, 0, &err);

	//pcre_study() returns NULL for both errors and when it can't optimize regex
	//check if error_str is NULL instead to distinguish the 2
	if(err != NULL){
		printf("ERROR :: Could not optimize '%s': %s\n",regexString, err);
		exit(1);
	}

	unsigned int offset = 0;
	unsigned int len = strlen(source);

	while( offset < len)
	{
		retval = pcre_exec(compiled_regex, study_val, source, strlen(source),offset, 0, substr_offset, 30);

		printf("# of matches found: %2d\n",retval);

		if(retval < 0){
			switch(retval){
				case PCRE_ERROR_NOMATCH:
					printf("WARN :: Pattern not found in string\n");
					break;

				case PCRE_ERROR_NULL:
					printf("WARN :: Something was NULL\n");
					break;

				case PCRE_ERROR_BADOPTION:
					printf("WARN :: Bad option was passed\n");
					break;

				case PCRE_ERROR_BADMAGIC:
					printf("WARN :: Bad magic number (compiled regex corrupt?)\n");
					break;

				case PCRE_ERROR_UNKNOWN_NODE:
					printf("WARN: Error in compiled regex\n");
					break;

				case PCRE_ERROR_NOMEMORY:
					printf("WARN: Out of memory\n");
					break;

				default:
					printf("WARN: Unknown error\n");
					break;
			}
			break;
		}

		//retval contains the number of substring matches found
		if(retval == 0)
		{
			printf("Too many substrings were found to fit in substr_offset\n");
			//Set to max # of substring matches possible
			retval = 30 / 3; //Documentation -> elements in vector of offsets is multiple of 3
		}

		int j = 0;
		for(; j < retval; j++)
		{
			pcre_get_substring(source, substr_offset, retval, j, &(match));
			printf("Match: %s\n",match);
			pcre_free_substring(match);	//memory allocated by the function
		}

		offset += substr_offset[(retval - 1)*2+1];	//set start of search to after matched string
	}

	pcre_free(compiled_regex);

	if(study_val != NULL)
	{
#ifdef PCRE_CONFIG_JIT
		pcre_free_study(study_val);
#else
		pcre_free(study_val);
#endif
	}

	return 0;
}
