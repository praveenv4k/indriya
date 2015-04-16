using System;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Security.Policy;
using System.Web;

namespace ExperimotWeb
{
    /// <summary>
    /// Summary description for RequestHandler
    /// </summary>
    public class DaeRequestHandler: IHttpHandler
    {
        private  string _fullpath;

        public DaeRequestHandler(string fullpath)
        {
            _fullpath = fullpath;
            //
            // TODO: Add constructor logic here
            //
        }

        public DaeRequestHandler()
        {
        }

        public void ProcessRequest(HttpContext context)
        {
            //var urlObject = urlParser.parse(context.Request.Url.PathAndQuery, true);
            var pathname = context.Request.Url.AbsolutePath;
            var physicalPath = context.Request.PhysicalPath;
            Console.WriteLine(pathname);

            if (string.IsNullOrEmpty(_fullpath))
            {
                _fullpath = physicalPath;
            }
            if (!string.IsNullOrEmpty(_fullpath))
            {

                if (System.IO.File.Exists(_fullpath))
                {
                    context.Response.WriteFile(_fullpath);
                }
                //using (var fs = new FileStream(_fullpath, FileMode.Open))
                //{
                //    using (StreamReader reader = new StreamReader(fs))
                //    {
                //        var contents = reader.ReadToEnd();
                        
                //    }
                //}
            }
            //var filePath = path.join(currentDir, pathname);

            //fs.stat(filePath, function(err, stats) {

            //    if (err) {
            //        response.writeHead(404, {});
            //        response.end('File not found!');
            //        return;
            //    }

            //    if (stats.isFile()) {

            //        fs.readFile(filePath, function(err, data) {

            //            if (err) {
            //                response.writeHead(404, {});
            //                response.end('Opps. Resource not found');
            //                return;
            //            }

            //            response.writeHead(200, {});
            //            response.write(data);
            //            response.end();
            //        });

            //    } else if (stats.isDirectory()) {

            //        fs.readdir(filePath, function(error, files) {

            //            if (error) {
            //                response.writeHead(500, {});
            //                response.end();
            //                return;
            //            }

            //            var l = pathname.length;
            //            if (pathname.substring(l-1)!='/') pathname += '/';

            //            response.writeHead(200, {'Content-Type': 'text/html'});
            //            response.write('<!DOCTYPE html>\n<html><head><meta charset="UTF-8"><title>' + filePath + '</title></head><body>');
            //            response.write('<h1>' + filePath + '</h1>');
            //            response.write('<ul style="list-style:none;font-family:courier new;">');
            //            files.unshift('.', '..');
            //            files.forEach(function(item) {

            //                var urlpath = pathname + item,
            //                    itemStats = fs.statSync(currentDir + urlpath);

            //                if (itemStats.isDirectory()) {
            //                    urlpath += '/';
            //                    item += '/';
            //                }

            //                response.write('<li><a href="'+ urlpath + '">' + item + '</a></li>');
            //            });

            //            response.end('</ul></body></html>');
            //        });
            //    }
            //});
        }

        public bool IsReusable
        {
            get { return false; }
        }
    }
}