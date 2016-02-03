
import subprocess,os,threading,urllib.request

#FNULL = open(os.devnull, 'w')    #use this if you want to suppress output to stdout from the subprocess
#filename = "my_file.dat"
#args = "cmd.exe ..\Debug\http-server.exe"
#subprocess.Popen(args, stdout=FNULL, stderr=FNULL, shell=True)



class MyThread(threading.Thread):
    def run(self):
        os.system("..\Debug\http-server.exe")
        print("process died")
        pass


thread = MyThread()
thread.daemon = True
thread.start()

print("got this far")
contents = urllib.request.urlopen("http://localhost:" + str(13374)).read()

print(contents)


