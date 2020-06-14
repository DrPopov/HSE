using System;
using System.Collections.Generic;
using System.Text;

namespace laba6.Handlers
{
    public class WholesaleHandler: Handler
    {
        public override void Handle(Order order) {
            if (order.Count > 10) {
                Console.WriteLine("В заказе больше 10 единиц товара. Выполняем оптовый заказ!");
                order.Number = "OP-" + Guid.NewGuid().ToString();
            } else {
                if (Successor != null)
                    Successor.Handle(order);
            }
        }
    }
}
