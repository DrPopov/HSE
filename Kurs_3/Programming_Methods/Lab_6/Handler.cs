using System;
using System.Collections.Generic;
using System.Text;

namespace laba6.Handlers
{
    public abstract class Handler
    {
        public Handler Successor { get; set; }

        public abstract void Handle(Order order);
    }
}
