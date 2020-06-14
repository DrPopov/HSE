using System;

namespace SingletonLaba
{
    class Program
    {
        static void Main(string[] args) {
            for (int i = 0; i < 10; ++i) {
                WriteWarning();
                WriteError();
                WriteNormal();
            }
            Logger logger = Logger.GetInstance();
            logger.Show(10);
        }

        static void WriteWarning() {
            Logger logger = Logger.GetInstance();
            logger.AddWarning("Warning!");
        }

        static void WriteNormal() {
            Logger logger = Logger.GetInstance();
            logger.AddNormal("It's Ok!");
        }

        static void WriteError() {
            Logger logger = Logger.GetInstance();
            logger.AddError("Error!!!");
        }
    }
}
