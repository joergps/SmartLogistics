/* $Id: fhem.js 9776 2015-11-04 13:36:53Z rapster $ */

CodeMirror.defineMode("fhem",function(){function d(a,c,d,f,b){c.chain=null;c.style=null;c.tail=null;c.tokenize=function(a,c){for(var h=!1,l,k=0;l=a.next();){if(l===d[k]&&!h){void 0!==d[++k]?(c.chain=d[k],c.style=f,c.tail=b):b&&a.eatWhile(b);c.tokenize=n;break}h=!h&&"\\"==l}return f};return c.tokenize(a,c)}function h(a,c,d){c.tokenize=function(a,b){a.string==d&&(b.tokenize=n);a.skipToEnd();return"string"};return c.tokenize(a,c)}function n(a,c){if(a.eatSpace())return null;if(c.chain)return d(a,c,c.chain,
c.style,c.tail);if(a.match(/^\-?[\d\.]/,!1)&&a.match(/^(\-?(\d*\.\d+(e[+-]?\d+)?|\d+\.\d*)|0x[\da-fA-F]+|0b[01]+|\d+(e[+-]?\d+)?)/))return"number";if(a.match(/^<<(?=\w)/))return a.eatWhile(/\w/),h(a,c,a.current().substr(2));if(a.sol()&&a.match(/^\=item(?!\w)/))return h(a,c,"=cut");var g=a.next();if('"'==g||"'"==g){if(a.prefix(3)=="<<"+g){var m=a.pos;a.eatWhile(/\w/);var b=a.current().substr(1);if(b&&a.eat(g))return h(a,c,b);a.pos=m}return d(a,c,[g],"string")}if("q"==g&&(b=a.look(-2),!b||!/\w/.test(b)))if(b=
a.look(0),"x"==b){b=a.look(1);if("("==b)return a.eatSuffix(2),d(a,c,[")"],"string-2",f);if("["==b)return a.eatSuffix(2),d(a,c,["]"],"string-2",f);if("{"==b)return a.eatSuffix(2),d(a,c,["}"],"string-2",f);if("<"==b)return a.eatSuffix(2),d(a,c,[">"],"string-2",f);if(/[\^'"!~\/]/.test(b))return a.eatSuffix(1),d(a,c,[a.eat(b)],"string-2",f)}else if("q"==b){b=a.look(1);if("("==b)return a.eatSuffix(2),d(a,c,[")"],"string");if("["==b)return a.eatSuffix(2),d(a,c,["]"],"string");if("{"==b)return a.eatSuffix(2),
d(a,c,["}"],"string");if("<"==b)return a.eatSuffix(2),d(a,c,[">"],"string");if(/[\^'"!~\/]/.test(b))return a.eatSuffix(1),d(a,c,[a.eat(b)],"string")}else if("w"==b){b=a.look(1);if("("==b)return a.eatSuffix(2),d(a,c,[")"],"bracket");if("["==b)return a.eatSuffix(2),d(a,c,["]"],"bracket");if("{"==b)return a.eatSuffix(2),d(a,c,["}"],"bracket");if("<"==b)return a.eatSuffix(2),d(a,c,[">"],"bracket");if(/[\^'"!~\/]/.test(b))return a.eatSuffix(1),d(a,c,[a.eat(b)],"bracket")}else if("r"==b){b=a.look(1);if("("==
b)return a.eatSuffix(2),d(a,c,[")"],"string-2",f);if("["==b)return a.eatSuffix(2),d(a,c,["]"],"string-2",f);if("{"==b)return a.eatSuffix(2),d(a,c,["}"],"string-2",f);if("<"==b)return a.eatSuffix(2),d(a,c,[">"],"string-2",f);if(/[\^'"!~\/]/.test(b))return a.eatSuffix(1),d(a,c,[a.eat(b)],"string-2",f)}else if(/[\^'"!~\/(\[{<]/.test(b)){if("("==b)return a.eatSuffix(1),d(a,c,[")"],"string");if("["==b)return a.eatSuffix(1),d(a,c,["]"],"string");if("{"==b)return a.eatSuffix(1),d(a,c,["}"],"string");if("<"==
b)return a.eatSuffix(1),d(a,c,[">"],"string");if(/[\^'"!~\/]/.test(b))return d(a,c,[a.eat(b)],"string")}if("m"==g&&(b=a.look(-2),!b||!/\w/.test(b))&&(b=a.eat(/[(\[{<\^'"!~\/]/))){if(/[\^'"!~\/]/.test(b))return d(a,c,[b],"string-2",f);if("("==b)return d(a,c,[")"],"string-2",f);if("["==b)return d(a,c,["]"],"string-2",f);if("{"==b)return d(a,c,["}"],"string-2",f);if("<"==b)return d(a,c,[">"],"string-2",f)}if("s"==g&&(b=/[\/>\]})\w]/.test(a.look(-2)),!b&&(b=a.eat(/[(\[{<\^'"!~\/]/)))||"y"==g&&(b=/[\/>\]})\w]/.test(a.look(-2)),
!b&&(b=a.eat(/[(\[{<\^'"!~\/]/)))||"t"==g&&(b=/[\/>\]})\w]/.test(a.look(-2)),!b&&(b=a.eat("r")))&&(b=a.eat(/[(\[{<\^'"!~\/]/)))return"["==b?d(a,c,["]","]"],"string-2",f):"{"==b?d(a,c,["}","}"],"string-2",f):"<"==b?d(a,c,[">",">"],"string-2",f):"("==b?d(a,c,[")",")"],"string-2",f):d(a,c,[b,b],"string-2",f);if("`"==g)return d(a,c,[g],"variable-2");if("/"==g)return/~\s*$/.test(a.prefix())?d(a,c,[g],"string-2",f):"operator";if("$"==g){m=a.pos;if(a.eatWhile(/\d/)||a.eat("{")&&a.eatWhile(/\d/)&&a.eat("}"))return"variable-2";
a.pos=m}if(/[$@%]/.test(g)){m=a.pos;if(a.eat("^")&&a.eat(/[A-Z]/)||!/[@$%&]/.test(a.look(-2))&&a.eat(/[=|\\\-#?@;:&`~\^!\[\]*'"$+.,\/<>()]/))if(b=a.current(),p[b])return"variable-2";a.pos=m}if(/[$@%&]/.test(g)&&(a.eatWhile(/[\w$\[\]]/)||a.eat("{")&&a.eatWhile(/[\w$\[\]]/)&&a.eat("}")))return b=a.current(),p[b]?"variable-2":"variable";if("#"==g&&"$"!=a.look(-2))return a.skipToEnd(),"comment";if(/[:+\-\^*$&%@=<>!?|\/~\.]/.test(g)){m=a.pos;a.eatWhile(/[:+\-\^*$&%@=<>!?|\/~\.]/);if(p[a.current()])return"operator";
a.pos=m}if("_"==g&&1==a.pos){if("_END__"==a.suffix(6))return d(a,c,["\x00"],"comment");if("_DATA__"==a.suffix(7))return d(a,c,["\x00"],"variable-2");if("_C__"==a.suffix(7))return d(a,c,["\x00"],"string")}if(/\w/.test(g)){m=a.pos;if("{"==a.look(-2)&&("}"==a.look(0)||a.eatWhile(/\w/)&&"}"==a.look(0)))return"string";a.pos=m}if(/[A-Z]/.test(g)){var e=a.look(-2),m=a.pos;a.eatWhile(/[A-Z_]/);if(/[\da-z]/.test(a.look(0)))a.pos=m;else{b=p[a.current()];if(!b)return"meta";b[1]&&(b=b[0]);return":"!=e?1==b?"keyword":
2==b?"def":3==b?"atom":4==b?"operator":5==b?"variable-2":"meta":"meta"}}if(/[a-zA-Z_]/.test(g)){e=a.look(-2);a.eatWhile(/\w/);b=p[a.current()];if(!b)return"meta";b[1]&&(b=b[0]);return":"!=e?1==b?"keyword":2==b?"def":3==b?"atom":4==b?"operator":5==b?"variable-2":"meta":"meta"}return null}var p={"->":4,"++":4,"--":4,"**":4,"=~":4,"!~":4,"*":4,"/":4,"%":4,x:4,"+":4,"-":4,".":4,"<<":4,">>":4,"<":4,">":4,"<=":4,">=":4,lt:4,gt:4,le:4,ge:4,"==":4,"!=":4,"<=>":4,eq:4,ne:4,cmp:4,"~~":4,"&":4,"|":4,"^":4,"&&":4,
"||":4,"//":4,"..":4,"...":4,"?":4,":":4,"=":4,"+=":4,"-=":4,"*=":4,",":4,"=>":4,"::":4,not:4,and:4,or:4,xor:4,BEGIN:[5,1],END:[5,1],PRINT:[5,1],PRINTF:[5,1],GETC:[5,1],READ:[5,1],READLINE:[5,1],DESTROY:[5,1],TIE:[5,1],TIEHANDLE:[5,1],UNTIE:[5,1],STDIN:5,STDIN_TOP:5,STDOUT:5,STDOUT_TOP:5,STDERR:5,STDERR_TOP:5,$ARG:5,$_:5,"@ARG":5,"@_":5,$LIST_SEPARATOR:5,'$"':5,$PROCESS_ID:5,$PID:5,$$:5,$REAL_GROUP_ID:5,$GID:5,"$(":5,$EFFECTIVE_GROUP_ID:5,$EGID:5,"$)":5,$PROGRAM_NAME:5,$0:5,$SUBSCRIPT_SEPARATOR:5,
$SUBSEP:5,"$;":5,$REAL_USER_ID:5,$UID:5,"$<":5,$EFFECTIVE_USER_ID:5,$EUID:5,"$>":5,$a:5,$b:5,$COMPILING:5,"$^C":5,$DEBUGGING:5,"$^D":5,"${^ENCODING}":5,$ENV:5,"%ENV":5,$SYSTEM_FD_MAX:5,"$^F":5,"@F":5,"${^GLOBAL_PHASE}":5,"$^H":5,"%^H":5,"@INC":5,"%INC":5,$INPLACE_EDIT:5,"$^I":5,"$^M":5,$OSNAME:5,"$^O":5,"${^OPEN}":5,$PERLDB:5,"$^P":5,$SIG:5,"%SIG":5,$BASETIME:5,"$^T":5,"${^TAINT}":5,"${^UNICODE}":5,"${^UTF8CACHE}":5,"${^UTF8LOCALE}":5,$PERL_VERSION:5,"$^V":5,"${^WIN32_SLOPPY_STAT}":5,$EXECUTABLE_NAME:5,
"$^X":5,$1:5,$MATCH:5,"$&":5,"${^MATCH}":5,$PREMATCH:5,"$`":5,"${^PREMATCH}":5,$POSTMATCH:5,"$'":5,"${^POSTMATCH}":5,$LAST_PAREN_MATCH:5,"$+":5,$LAST_SUBMATCH_RESULT:5,"$^N":5,"@LAST_MATCH_END":5,"@+":5,"%LAST_PAREN_MATCH":5,"%+":5,"@LAST_MATCH_START":5,"@-":5,"%LAST_MATCH_START":5,"%-":5,$LAST_REGEXP_CODE_RESULT:5,"$^R":5,"${^RE_DEBUG_FLAGS}":5,"${^RE_TRIE_MAXBUF}":5,$ARGV:5,"@ARGV":5,ARGV:5,ARGVOUT:5,$OUTPUT_FIELD_SEPARATOR:5,$OFS:5,"$,":5,$INPUT_LINE_NUMBER:5,$NR:5,"$.":5,$INPUT_RECORD_SEPARATOR:5,
$RS:5,"$/":5,$OUTPUT_RECORD_SEPARATOR:5,$ORS:5,"$\\":5,$OUTPUT_AUTOFLUSH:5,"$|":5,$ACCUMULATOR:5,"$^A":5,$FORMAT_FORMFEED:5,"$^L":5,$FORMAT_PAGE_NUMBER:5,"$%":5,$FORMAT_LINES_LEFT:5,"$-":5,$FORMAT_LINE_BREAK_CHARACTERS:5,"$:":5,$FORMAT_LINES_PER_PAGE:5,"$=":5,$FORMAT_TOP_NAME:5,"$^":5,$FORMAT_NAME:5,"$~":5,"${^CHILD_ERROR_NATIVE}":5,$EXTENDED_OS_ERROR:5,"$^E":5,$EXCEPTIONS_BEING_CAUGHT:5,"$^S":5,$WARNING:5,"$^W":5,"${^WARNING_BITS}":5,$OS_ERROR:5,$ERRNO:5,"$!":5,"%OS_ERROR":5,"%ERRNO":5,"%!":5,$CHILD_ERROR:5,
"$?":5,$EVAL_ERROR:5,"$@":5,$OFMT:5,"$#":5,"$*":5,$ARRAY_BASE:5,"$[":5,$OLD_PERL_VERSION:5,"$]":5,"if":[1,1],elsif:[1,1],"else":[1,1],"while":[1,1],unless:[1,1],"for":[1,1],foreach:[1,1],abs:1,accept:1,alarm:1,atan2:1,bind:1,binmode:1,bless:1,bootstrap:1,"break":1,caller:1,chdir:1,chmod:1,chomp:1,chop:1,chown:1,chr:1,chroot:1,close:1,closedir:1,connect:1,"continue":[1,1],cos:1,crypt:1,dbmclose:1,dbmopen:1,"default":1,defined:1,"delete":1,die:1,"do":1,dump:1,each:1,endgrent:1,endhostent:1,endnetent:1,
endprotoent:1,endpwent:1,endservent:1,eof:1,eval:1,exec:1,exists:1,exit:1,exp:1,fcntl:1,fileno:1,flock:1,fork:1,format:1,formline:1,getc:1,getgrent:1,getgrgid:1,getgrnam:1,gethostbyaddr:1,gethostbyname:1,gethostent:1,getlogin:1,getnetbyaddr:1,getnetbyname:1,getnetent:1,getpeername:1,getpgrp:1,getppid:1,getpriority:1,getprotobyname:1,getprotobynumber:1,getprotoent:1,getpwent:1,getpwnam:1,getpwuid:1,getservbyname:1,getservbyport:1,getservent:1,getsockname:1,getsockopt:1,given:1,glob:1,gmtime:1,"goto":1,
grep:1,hex:1,"import":1,index:1,"int":1,ioctl:1,join:1,keys:1,kill:1,last:1,lc:1,lcfirst:1,length:1,link:1,listen:1,local:2,localtime:1,lock:1,log:1,lstat:1,m:null,map:1,mkdir:1,msgctl:1,msgget:1,msgrcv:1,msgsnd:1,my:2,"new":1,next:1,no:1,oct:1,open:1,opendir:1,ord:1,our:2,pack:1,"package":1,pipe:1,pop:1,pos:1,print:1,printf:1,prototype:1,push:1,q:null,qq:null,qr:null,quotemeta:null,qw:null,qx:null,rand:1,read:1,readdir:1,readline:1,readlink:1,readpipe:1,recv:1,redo:1,ref:1,rename:1,require:1,reset:1,
"return":1,reverse:1,rewinddir:1,rindex:1,rmdir:1,s:null,say:1,scalar:1,seek:1,seekdir:1,select:1,semctl:1,semget:1,semop:1,send:1,setgrent:1,sethostent:1,setnetent:1,setpgrp:1,setpriority:1,setprotoent:1,setpwent:1,setservent:1,setsockopt:1,shift:1,shmctl:1,shmget:1,shmread:1,shmwrite:1,shutdown:1,sin:1,sleep:1,socket:1,socketpair:1,sort:1,splice:1,split:1,sprintf:1,sqrt:1,srand:1,stat:1,state:1,study:1,sub:1,substr:1,symlink:1,syscall:1,sysopen:1,sysread:1,sysseek:1,system:1,syswrite:1,tell:1,telldir:1,
tie:1,tied:1,time:1,times:1,tr:null,truncate:1,uc:1,ucfirst:1,umask:1,undef:1,unlink:1,unpack:1,unshift:1,untie:1,use:1,utime:1,values:1,vec:1,wait:1,waitpid:1,wantarray:1,warn:1,when:1,write:1,define:2,attr:2,at:2,notify:2,set:2,ReadingsVal:1,Value:1,fhem:1,IF:2,DOIF:2,DOELSE:2,DOELSEIF:2,y:null};keywords.foreach(function(a,c){p[c]=2});var f=/[goseximacplud]/;return{startState:function(){return{tokenize:n,chain:null,style:null,tail:null}},token:function(a,c){return(c.tokenize||n)(a,c)},electricChars:"{}"}});
CodeMirror.defineMIME("text/x-fhem","fhem");CodeMirror.StringStream.prototype.look=function(d){return this.string.charAt(this.pos+(d||0))};CodeMirror.StringStream.prototype.prefix=function(d){if(d){var h=this.pos-d;return this.string.substr(0<=h?h:0,d)}return this.string.substr(0,this.pos-1)};CodeMirror.StringStream.prototype.suffix=function(d){var h=this.string.length,n=h-this.pos+1;return this.string.substr(this.pos,d&&d<h?d:n)};
CodeMirror.StringStream.prototype.nsuffix=function(d){var h=this.pos;d=d||this.string.length-this.pos+1;this.pos+=d;return this.string.substr(h,d)};CodeMirror.StringStream.prototype.eatSuffix=function(d){d=this.pos+d;var h;0>=d?this.pos=0:d>=(h=this.string.length-1)?this.pos=h:this.pos=d};Array.prototype.foreach=function(d){for(var h=0;h<this.length;h++)d(h,this[h])};CodeMirror.commands.autocomplete=function(d){CodeMirror.showHint(d,CodeMirror.hint.fhem,{async:!0})};
var keywords="at attr define delete deleteattr deletereading IF DOIF DOELSEIF DOELSE displayattr fhem get getstate list modify notify set setdefaultattr setreading setstate trigger AttrVal OldTimestamp OldValue ReadingsVal ReadingsTimestamp Value".split(" "),variables="$defs $hms $hour $isdst $mday $min $month $sec $wday $we $yday $year".split(" "),devices=[];
CodeMirror.registerHelper("hint","fhem",function hintfhem(h,n,p){function f(a){var b=[];null!=a&&(a.PossibleAttrs.split(" ").foreach(function(a,c){b.push(c.split(":")[0])}),b.sort(function(a,b){return a.toLowerCase().localeCompare(b.toLowerCase())}));return b}function a(a){var b=[];null!=a&&(a.PossibleSets.split(" ").foreach(function(a,c){b.push(c.split(":")[0])}),b.sort(function(a,b){return a.toLowerCase().localeCompare(b.toLowerCase())}));return b}function c(a){var b=[];if(null!=a){for(var c in a.Readings)b.push(c);
b.sort(function(a,b){return a.toLowerCase().localeCompare(b.toLowerCase())})}return b}function g(a,b){var c=0,e=a.length-1,f=Math.floor((e+c)/2),g=null;for(b=b.toLowerCase();(g=a[f].Name.toLowerCase())!=b&&c<e;)b<g?e=f-1:b>g&&(c=f+1),f=Math.floor((e+c)/2);return g!=b?null:a[f]}function m(a,b,c,e){var f=[];a.foreach(function(a,b){0==b.lastIndexOf(e,0)&&f.push({text:b,className:"hintkeyword"})});b.foreach(function(a,b){0==b.Name.lastIndexOf(e,0)&&(b.Attributes&&null!=b.Attributes.alias?f.push({text:b.Name,
displayText:b.Name+" # "+b.Attributes.alias}):f.push(b.Name))});c.foreach(function(a,b){0==b.lastIndexOf(e,0)&&f.push({text:b,className:"hintvariable"})});n({list:f,from:CodeMirror.Pos(t.line,u),to:CodeMirror.Pos(t.line,r)})}if(0==devices.length)$.getJSON("/fhem?cmd=jsonlist2&XHR=1",function(a){0==devices.length&&(a.Results.foreach(function(a,b){devices.push(b)}),devices.sort(function(a,b){return a.Name.toLowerCase().localeCompare(b.Name.toLowerCase())}),hintfhem(h,n,p))});else{var b=keywords,e=variables,
q=devices,t=h.getCursor(),l=h.getTokenAt(t),k=l.string,u=l.start,r=l.end;/[^\w$_-]/.test(k)&&(k="",u=r=t.ch);l=h.getLine(t.line).substr(0,r);/^[ \t]*(attr|set|get|delete|deleteattr|deletereading|displayattr|getstate|list|modify|setdefaultattr|setreading|setstate|trigger)[ \t]+([\w]*)$/.test(l)?b=e=[]:/^[ \t]*(attr|deleteattr|displayattr)[ \t]+(\w+)[ \t]+([\w-]*)$/.test(l)?(b=q=e=[],e=RegExp.$2,k=RegExp.$3,e=g(devices,e),e=f(e)):/^[ \t]*(DOIF|DOELSE|DOELSEIF).*\[+\??(\w+):\??([\w-]*)$/.test(l)?(b=
q=e=[],e=RegExp.$2,k=RegExp.$3,e=g(devices,e),e=c(e)):/^[ \t]*(deletereading|setreading)[ \t]+(\w+)[ \t]+([\w-]*)$/.test(l)?(b=q=e=[],e=RegExp.$2,k=RegExp.$3,e=g(devices,e),e=c(e)):/^[ \t]*(set|get)[ \t]+(\w+)[ \t]+([\w-]*)$/.test(l)?(b=q=e=[],e=RegExp.$2,k=RegExp.$3,e=g(devices,e),e=a(e)):/.*(AttrVal)[ \t]*\([ \t]*\"(\w+)\"[ \t]*,[ \t]*\"([\w-]*)$/.test(l)?(b=q=e=[],e=RegExp.$2,k=RegExp.$3,u=r-k.length,e=g(devices,e),e=f(e)):/.*(ReadingsVal|ReadingsTimestamp)[ \t]*\([ \t]*\"(\w+)\"[ \t]*,[ \t]*\"([\w-]*)$/.test(l)?
(b=q=e=[],e=RegExp.$2,k=RegExp.$3,u=r-k.length,e=g(devices,e),e=c(e)):/.*(OldTimestamp|OldValue|Value|ReadingsVal|ReadingsTimestamp|AttrVal)[ \t]*\([ \t]*\"(\w*)$/.test(l)&&(b=e=[],k=RegExp.$2,u=r-k.length);m(b,q,e,k)}});