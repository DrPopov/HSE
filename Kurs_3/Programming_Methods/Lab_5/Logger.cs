using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SingletonLaba
{
    public class Logger
    {
        private static readonly Lazy<Logger> logger =
            new Lazy<Logger>(() => new Logger());

        private List<Event> Events { get; set; }

        private Logger() {
            Events = new List<Event>();
        }

        public void AddNormal(string text) =>
            Events.Add(new Event(text, EventLevel.Normal));

        public void AddWarning(string text) =>
            Events.Add(new Event(text, EventLevel.Warning));

        public void AddError(string text) =>
            Events.Add(new Event(text, EventLevel.Error));

        public void Show(int count) =>
            Events.TakeLast(count).ToList().ForEach(x => x.Show());

        public static Logger GetInstance() {
            return logger.Value;
        }

        private class Event
        {
            private DateTime Time { get; set; }

            private EventLevel EventLevel { get; set; }

            private string Message { get; set; }

            public Event(string message, EventLevel level) {
                Message = message;
                EventLevel = level;
                Time = DateTime.Now;
            }

            public void Show() {
                if (this.EventLevel == EventLevel.Normal)
                    Console.ForegroundColor = ConsoleColor.Green;
                if (this.EventLevel == EventLevel.Warning)
                    Console.ForegroundColor = ConsoleColor.Yellow;
                if (this.EventLevel == EventLevel.Error)
                    Console.ForegroundColor = ConsoleColor.Red;

                Console.WriteLine($"{Time.ToString()}: {Message}");

                Console.ResetColor();
            }
        }

        private enum EventLevel
        {
            Normal,
            Warning,
            Error
        }
    }
}
