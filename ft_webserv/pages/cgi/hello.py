#! /usr/bin/python
import datetime

print("Content-type:text/html\r\n\r\n")
print('<html>')
print('<head>')
print('<title>Hello Word - First CGI Program</title>')
print('</head>')
print('<body>')
print('<h2>Hello evaluator! This is SAMATHE\'s first CGI program</h2>')
print(f'Today is {datetime.date.today()}<br>')
print(f'Current time is {datetime.datetime.now().strftime("%H:%M:%S")}<br>')
print('</body>')
print('</html>')