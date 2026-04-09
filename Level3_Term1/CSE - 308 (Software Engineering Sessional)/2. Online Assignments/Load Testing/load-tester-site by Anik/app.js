const http = require('http');
const fs = require('fs');
const qs = require('querystring');
const url = require('url');
let isProcessing = false;

const server = http.createServer((req, res) => {
    if (req.url === '/' && req.method === 'GET') {
        // Serve the home.html file
        fs.readFile('home.html', (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Internal Server Error');
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data);
            }
        });
    } 
    else if (req.url.startsWith('/apply') && req.method === 'GET') {
        // Parse the URL to extract query parameters
        const parsedUrl = url.parse(req.url, true);
        const studentId = parsedUrl.query.studentId;

        // Check if studentId exists in data.json
        fs.readFile('data.json', 'utf8', (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Internal Server Error');
                return;
            }

            const students = JSON.parse(data);
            const studentExists = students.some(student => student.id === studentId);

            if (studentExists) {
                console.log(`Sorry! Id ${studentId} already Applied...`)
                // Redirect to status.html with status=alreadyApplied
                res.writeHead(302, { 'Location': '/status?status=alreadyApplied' });
                res.end();
            } else {
                // Serve the apply.html file with pre-filled studentId
                fs.readFile('apply.html', 'utf8', (err, applyData) => {
                    if (err) {
                        res.writeHead(500, { 'Content-Type': 'text/plain' });
                        res.end('Internal Server Error');
                    } else {
                        // Replace the placeholder with studentId
                        const modifiedData = applyData.replace('STUDENT_ID', studentId);
                        res.writeHead(200, { 'Content-Type': 'text/html' });
                        res.end(modifiedData);
                    }
                });
            }
        });
    } 
    else if (req.url.startsWith('/apply') && req.method === 'POST') {
        // Parse the request body for POST requests to /apply
        let body = '';
        req.on('data', (chunk) => {
            body += chunk.toString();
        });
        req.on('end', () => {
            const formData = qs.parse(body);
            const studentId = formData.studentId;
            const name = formData.name;

            // Save application data to data.json
            fs.readFile('data.json', 'utf8', (err, data) => {
                if (err) {
                    res.writeHead(500, { 'Content-Type': 'text/plain' });
                    res.end('Internal Server Error');
                    return;
                }

                const students = JSON.parse(data);


                const studentExists = students.some(student => student.id === studentId);

                if (studentExists) {
                    // Redirect to status.html with status=alreadyApplied
                    //console.log('Sorry! Already Applied...')
                    res.writeHead(302, { 'Location': '/status?status=alreadyApplied' });
                    res.end();
                }
                else{
                    students.push({ id: studentId, name: name });

                    fs.writeFile('data.json', JSON.stringify(students, null, 2), (err) => {
                        if (err) {
                            res.writeHead(500, { 'Content-Type': 'text/plain' });
                            res.end('Internal Server Error');
                        } else {
                            console.log(`Application Successful for Id ${studentId}`)
                            // Redirect to status.html with status=applicationSuccessful
                            res.writeHead(302, { 'Location': '/status?status=applicationSuccessful' });
                            res.end();
                        }
                    });
                }
            });
            
            // For now, let's just send a response indicating successful submission
            // res.writeHead(200, { 'Content-Type': 'text/plain' });
            // res.end('Application Submitted Successfully');
        });
    }
    else if (req.url.startsWith('/status') && req.method === 'GET') {
        // Parse the URL to extract query parameters
        const parsedUrl = url.parse(req.url, true);
        const status = parsedUrl.query.status || 'Unknown Status';
    
        // Read the status.html file
        fs.readFile('status.html', 'utf8', (err, htmlContent) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Internal Server Error');
            } else {
                // Replace the placeholder with the status
                
                const statusMessage = status === 'alreadyApplied' ? 'Already Applied' :
                                      status === 'applicationSuccessful' ? 'Application Successful' :
                                      'Unknown Status';

                const modifiedHtml = htmlContent.replace('STATUS', statusMessage);
    
                // Serve the modified HTML
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(modifiedHtml);
            }
        });
    }
    else if (req.url === '/students' && req.method === 'GET') {
        // Serve student data as JSON
        fs.readFile('data.json', 'utf8', (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Internal Server Error');
            } else {
                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(data);
            }
        });
    }
    else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end('404 Not Found');
    }
});


// change here
const local_IP = '192.168.0.197'

const PORT = 3000;
server.listen(PORT, local_IP, () => {
    console.log(`Server is running on port ${PORT}`);
});
