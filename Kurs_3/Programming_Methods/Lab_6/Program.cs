using laba6.Handlers;
using System;

namespace laba6
{
    class Program
    {
        static void Main(string[] args) {
            Handler partner = new PartnerHandler();
            Handler foreigner = new ForeignerHandler();
            Handler wholesale = new WholesaleHandler();
            Handler normal = new NormalHandler();
            partner.Successor = foreigner;
            foreigner.Successor = wholesale;
            wholesale.Successor = normal;

            partner.Handle(new Order(100, ClientType.Foreigner));
            partner.Handle(new Order(1, ClientType.Partner));
            partner.Handle(new Order(5, ClientType.Normal));
            partner.Handle(new Order(50, ClientType.Normal));
        }
    }
}
