extern FILE *targetFile;

void init_code(){
	targetFile = fopen("targetFile.xsm", "w");
	fprintf(targetFile, "0\n2056\n0\n0\n0\n0\n0\n0\n");
	fprintf(targetFile, "ADD SP, 26\n");
}
