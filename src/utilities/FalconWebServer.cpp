/**
 * socket program web server
 */

#include "FalconWebServer.h"

#define PORT "8888"  // the port users will be connecting to

#define BACKLOG 10     // how many pending connections queue will hold

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int run()
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv,numbytes;
    char inputBuffer[400];
    CommandLine cl;
    FileUtil util;


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }
        //


        numbytes = recv(new_fd, inputBuffer, sizeof inputBuffer, 0);
        inputBuffer[numbytes] = '\0';
        std::string inpbf(inputBuffer);

        //printf("input received:%d  and %s \n",numbytes,inputBuffer);
        //printf("input is:%s \n",inputBuffer[0]);

        std::string inputdata=" ";

        //cout<<"input:"<<inpbf<<endl;

        string::const_iterator start, end;
        boost::match_results<std::string::const_iterator> what;
        boost::match_flag_type flags = boost::match_default;

        //get input from incoming request here
        regex expr_ref("(GET)(\\s+)(\\/)(query=)(.*?)(\\s+)");
        	start = inpbf.begin();
        	end = inpbf.end();
        	while (boost::regex_search(start, end, what, expr_ref, flags)) {
        		inputdata = what[5];
        		break;
        	}

       cout<<"input:"<<inputdata<<endl;

        //input fetch code ends

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);
        std::string op;
        std::string response;
        list<size_t> qresp;
        if(inputdata.length()>0){
        	qresp = cl.runQueryWeb(inputdata);
        	response = "data";
        }else{
        	response = "empty";
        }


        std::string html_inner_content;
        std::string html_end_content;

        std::string title = "this is title";
        std::string link = "file path is here";
        std::string description = "description should have come here";

        std::string css = "<style type=\"text/css\">ol,ul,li{border:0;margin:0;padding:0}h3,.med{font-size:medium;font-weight:400}body{color:#222}li.head,li.g,body,html,.std,.c h2,#mbEnd h2,h1{font-size:small;font-family:arial,sans-serif}li.g{margin-top:0;margin-bottom:20px}ol li{list-style:none}li{line-height:1.2}#res h3.r{display:block;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}.vsc{display:inline-block;position:relative;width:100%}#ires h3,#res h3,#tads h3,#tadsb h3,#mbEnd h3{font-size:medium}.sl,.r{display:inline;font-weight:400;margin:0}.s{max-width:42em;color:#222}div{display:block}.kv,.kvs{display:block;margin-bottom:2px}.f,.f a:link,.m,.c h2,#mbEnd h2,#tads h2,#tadsb h2,#tadsto h2,.descbox{color:#666}.st,.ac{line-height:1.24}.a,cite,cite a:link,cite a:visited,.cite,.cite:link,#mbEnd cite b,#tads cite b,#tadsb cite b,#tadsto cite b,#ans > i,.bc a:link{color:#093;font-style:normal}a:link,.w,.q:active,.q:visited,.tbotu{color:#12C;cursor:pointer}</style>";


        vector<std::string> outputList;
        op="<html><head><title>Falcon Search Engine</title>" + css + "</head><body><h2>Falcon Search Engine - Team Mango</h2><form name=\"input\" action=\"http://localhost:8888\" method=\"post\" id=\"input\">Query: <input type=\"text\" id=\"queryId\" name=\"query\" value=\"query here\" /><input type=\"submit\" value=\"Submit\" /></form><ol>";


        BOOST_FOREACH(size_t t, qresp){

            html_inner_content="<li class=\"g\"><div class=\"vsc\"><h3 class=\"r\"><a href=\"#\">" + util.getStringValue(t) + "</a></h3><div class=\"s\"><div class=\"f kv\"><cite>" + link + "</cite></div><span class=\"st\">" + description + "</span></div></div></li>";
            op = op + html_inner_content;

        }

        op = op+ "</ol></body></html>";

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            if (send(new_fd,op.c_str() , op.length(), 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}
