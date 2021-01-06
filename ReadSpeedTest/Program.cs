using System;
using System.Diagnostics;
using System.IO;

namespace ReadSpeedTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var swTotal = new Stopwatch();
            var swAfterOpen = new Stopwatch();

            // Compile File.OpenRead
            using (var test = File.OpenRead(@"C:\trac_msi.log")) ;
            
            swTotal.Start();
            {
                using (var fs = File.OpenRead(args[0]))
                {
                    swAfterOpen.Start();

                    using (var outputStream = new NullStream()) {
                        fs.CopyTo(outputStream);
                        swAfterOpen.Stop();
                        swTotal.Stop();
                        Console.WriteLine("{0}", args[0]);
                        Console.WriteLine("After open:  {0}", PrintDetails(swAfterOpen, outputStream.Length));
                        Console.WriteLine("Before open: {0}", PrintDetails(swTotal, outputStream.Length));
                    }

                }
            }
        }

        static string PrintDetails(Stopwatch sw, long numBytes)
        {
            return string.Format("{0} bytes ({1:0} MB) copied, {2:0.000} s, {3:0.0} MB/s", numBytes, numBytes / 1024.0 / 1024, sw.ElapsedMilliseconds / 1000.0, (double) numBytes / (sw.ElapsedMilliseconds / 1000.0) / 1024 / 1024);
        }
    }
}
