using System;
using System.Collections.Generic;
using System.Text;

namespace laba6.Handlers
{
    public class NormalHandler:Handler
    {
        public override void Handle(Order order) {
            if (order.Count < 11) {
                Console.WriteLine("Выполняем обычный заказ!");
                order.Number = "NM-" + Guid.NewGuid().ToString();
            } else {
                if (Successor != null)
                    Successor.Handle(order);
            }
        }
    }
}
