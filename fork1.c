

int main()

for(i=0; i<10; i++)
{
cpid = fork();

if(cpid == 0){
	printf("cpid %d\n", getpid());
	exit(0);
}
else if(cpid > 0){
	print("cpid %d\n", cpid)
}}
